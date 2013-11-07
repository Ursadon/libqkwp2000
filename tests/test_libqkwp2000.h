#ifndef TEST_LIBWAKEPROTO_H
#define TEST_LIBWAKEPROTO_H

#include <QObject>
#include <qkwp2000.h>

class Test_libqkwp2000 : public QObject
{
    Q_OBJECT
public:
    explicit Test_libqkwp2000(QObject *parent = 0);
    QKWP2000 kwp;
signals:
    
public slots:

private slots: // must be private
    void kwp_test_tx_short();
    void kwp_test_tx_full();
    void lwp_test_rx();
//    void lwp_test_rx_continuous();
//    void lwp_test_rx_bruteforce();
};

#endif // TEST_LIBWAKEPROTO_H
