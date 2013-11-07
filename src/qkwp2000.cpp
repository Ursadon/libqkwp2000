/*
 * Copyright (c) 2013, Nikolay Lomakin <lomakin90@yandex.ru>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <QCoreApplication>
#include <QDebug>
#include "qkwp2000.h"

QKWP2000::QKWP2000()
{
    qDebug() << "[libQKWP2000][INFO]: QKWP2000 module loaded" << endl;
    rx_packet = 0;
}

QKWP2000::~QKWP2000()
{

}

void QKWP2000::test() {
    qDebug() << "[libQKWP2000][INFO]: QKWP2000 test" << endl;
}

/**
 * Create packet, based on input data
 *
 * @param cmd Command number
 * @param data A QByteArray of data to send
 * @return QByteArray with data in KWP packet
 */
QByteArray QKWP2000::createpacket(unsigned char cmd, QByteArray data) {
    QByteArray packet;
    unsigned char checksum = 0;

    if(data.size() < 64) {
        packet.prepend(0x80 + 1 + data.size());
    } else if (data.size() < 128) {
	packet.prepend(0x80 + 1);
	packet.append(data.size());
    } else {
        return 0;
    }
    packet.append(MSG_TARGET);
    packet.append(MSG_SRC);
    packet.append(cmd);
    packet.append(data);
    foreach(unsigned char byte, packet) {
        checksum += byte;
    }
    packet.append(checksum);

    return packet;
}

QByteArray QKWP2000::createpacket(unsigned char cmd) {
    QByteArray packet;
    unsigned char checksum = 0;

    packet.prepend(0x81);
    packet.append(MSG_TARGET);
    packet.append(MSG_SRC);
    packet.append(cmd);
    foreach(unsigned char byte, packet) {
        checksum += byte;
    }
    packet.append(checksum);

    return packet;
}

/**
 * Parse input data into packet
 *
 * @param data QByteArray of data to parse
 * @return No return
 */
int QKWP2000::getpacket(QByteArray data) {
    int num_of_bytes = 0;
    foreach (unsigned char rx_byte, data) {
	rx_packet.append(rx_byte);        
    }
    if(rx_packet.size() >= 3) {
	num_of_bytes = rx_packet.at(0) - 0x80;
	if (rx_packet.size() >= num_of_bytes) {
            dump_packet(rx_packet);
        }
    }    
    return 0;
}


/**
 * Print packet
 *
 * @param packet QByteArray wake packet
 */
void QKWP2000::dump_packet(QByteArray packet) {
    QString hexdata;
    unsigned int num_of_bytes = packet.at(0) - 0x80;
    unsigned int header = packet.at(0);
    unsigned int target = packet.at(1);
    unsigned int source = packet.at(2);
    unsigned int cmd = packet.at(3);
    QByteArray data = packet.mid(4,num_of_bytes);
//    unsigned int actual_crc = packet.at(4+packet.size());

    unsigned int i = 0;
   foreach(unsigned char c, data) {
        hexdata += "0x";
        hexdata += QString::number(c,16).toUpper();
        hexdata += " ";
        if (i == 7) {
            hexdata += "\n";
            i = 0;
        } else {
            i++;
        }
    }
    qDebug()
            << "---------------------------------------" << endl
            << "[QKWP2000][INFO]: Received packet" << endl
            << "TARGET:\t\t" << QString::number(static_cast<unsigned char>(target)) << endl
            << "SOURCE:\t\t" << QString::number(static_cast<unsigned char>(source)) << endl
            << "CMD:\t\t" << QString::number(static_cast<unsigned char>(cmd)) << endl
            << "DATA (raw):\t\t" << endl
            << qPrintable(QString(data)) << endl
            << "DATA (hex):\t\t" << endl
            << qPrintable(QString(hexdata)) << endl
            << "---------------------------------------" << endl;
}
