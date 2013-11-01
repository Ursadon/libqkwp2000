#ifndef _WAKEPROTO_H
#define _WAKEPROTO_H

#include <QCoreApplication>
#include <QtCore/QtGlobal>
#if defined(QKWP2000_LIBRARY)
#define QKWP2000_EXPORT Q_DECL_EXPORT
#else
#define QKWP2000_EXPORT Q_DECL_IMPORT
#endif

/* Idetifiers. Reply code is code+40 */
#define startCommunication			0x81
#define stopCommunication			0x82
#define startDiagnosticSession			0x10
#define stopDiagnosticSession			0x20
#define ecuReset				0x11
#define clearDiagnosticInformation		0x14
#define	readDiagnosticTroubleCodesByStatus	0x18
#define readEcuIdentification			0x1a
#define readDataByLocalIdentifier		0x21
#define readMemoryByAddress			0x23
#define inputOutputControlByLocalIdentifier	0x30
#define writeDataByLocalIdentifier		0x3b
#define testerPresent				0x3e

/* Reply codes */
#define generalReject			0x10
#define serviceNotSupported		0x11
#define subFunctionNotSupported 	0x12
#define busy-RepeatRequest		0x21
#define requestOutOfRange		0x31
#define transferAborted			0x72
#define blockTransferDataChecksumError	0x77


class QKWP2000_EXPORT QKWP2000 : public QObject
{
    Q_OBJECT
public:
    QKWP2000();
    ~QKWP2000();
    void test();
    QByteArray createpacket(unsigned char address, unsigned char cmd, QByteArray data);
    int getpacket(QByteArray datastream);
    void dump_packet(QByteArray packet);
private:
    enum PacketHeader { fend = 0, address, cmd, numofbytes, datastream, crc};
    bool packet_started, data_started;
    unsigned char num_of_bytes, byte_stuffing;
    QByteArray rx_temp_packet, rx_packet_data;
    QByteArray stuffing(QByteArray packet);
    unsigned int getcrc(QByteArray data);
signals:
    void packetReceived(QByteArray packet);
};

#endif // _WAKEPROTO_H
