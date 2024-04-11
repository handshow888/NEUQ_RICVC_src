#include "SerialCom.h"

shared_ptr<serial_port> SerialPort::serialPort = nullptr;
char SerialPort::receiveData[] = {0};
float SerialPort::pitch_now = 0.0f;
float SerialPort::yaw_now = 0.0f;

SerialPort::SerialPort() : portName("/dev/ttyUSB0"),
                           baudRate(115200)
{
    memset(receiveData, 0, sizeof(receiveData));
}

SerialPort::~SerialPort()
{
    this->write(0.26,1.0,0,0,0);
    // cout << "SerialPort析构函数" << endl;
    // usleep(5000000);
    if (serialPort == nullptr)
        {
            
            serialPort->close();  
        }

}

bool SerialPort::init(string port_name, uint baud_rate)
{
    portName = port_name;
    baudRate = baud_rate;

    return open();
}

void SerialPort::runService()
{
    startAsyncRead();
    io.run();
}

bool SerialPort::open()
{
    try
    {
        if (serialPort == nullptr)
            serialPort = shared_ptr<serial_port>(new serial_port(io));

        serialPort->open(portName, errorCode);

        // 设置串口参数
        serialPort->set_option(serial_port::baud_rate(baudRate));
        serialPort->set_option(serial_port::flow_control());
        serialPort->set_option(serial_port::parity());
        serialPort->set_option(serial_port::stop_bits());
        serialPort->set_option(serial_port::character_size(8));

        return true;
    }
    catch (exception &err)
    {
        cout << "Exception Error: " << err.what() << endl;
    }

    return false;
}

void SerialPort::startAsyncRead()
{
    memset(receiveData, 0, sizeof(receiveData));
    serialPort->async_read_some(boost::asio::buffer(receiveData),
                                boost::bind(handleRead,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));
}

void SerialPort::close()
{
    serialPort->close();
}

void SerialPort::write(float pitch, float yaw, int flag1, int flag2, int flag3)
{

    pitch = pitch * 100;
    yaw = yaw * 100;
    int s1, s2;

    s1 = (int)pitch;
    s2 = (int)yaw;

    uint8_t sent[sendlength]; // #define sendlength 34
    union Buffer
    {
        int data[(sendlength - 2) / 4];
        char char_data[(sendlength - 2)];
    } buffer2;
    //*******************对发出数据的赋予
    buffer2.data[0] = s1;
    buffer2.data[1] = s2;
    buffer2.data[2] = 1;
    buffer2.data[3] = 2;
    buffer2.data[4] = 3;
    // cout<<"Write_yaw:"<<s2<<"Write_pitch"<<s1<<endl;
    //*******************
    sent[0] = 0x2a;
    sent[sendlength - 1] = 0x3b;
    for (int i = 1; i < sendlength - 1; i++)
    {
        sent[i] = buffer2.char_data[i - 1];
                //buffer2.char_data[i - 1]=sent[i];

    }
        cout << "SEND: ";
        for (int ii = 0; ii < sendlength; ii++)
        {
            cout << setfill('0') << setw(2) << setiosflags(ios::uppercase) << hex << (int)(sent[ii]) << ' ';
        }
        cout << endl;

    uint32_t aaa = serialPort->write_some(boost::asio::buffer(sent));
}

void SerialPort::handleRead(const boost::system::error_code &ec, size_t byte_read)
{
    // boost::timer t_handleRead;

    union Buffer
    {
        short int data[(receivelength - 2) / 2]; // 2 byte
        char char_data[(receivelength - 2)];     // 1 byte
    } buffer1;

    for (int j = 0; j < (receivelength - 2); j++)
        buffer1.char_data[j] = receiveData[j + 1];
    if (receiveData[1] != 0)
    {
        SerialPort::yaw_now = buffer1.data[0] / 100.0;
        SerialPort::pitch_now = buffer1.data[1] / 100.0;
    }
    // cout<<"RESDyaw:"<<SerialPort::yaw_now<<endl;
    // cout<<"READpitch:"<<SerialPort::pitch_now<<endl;
    // cout<<"t_handleRead"<<t_handleRead.elapsed()<<endl;
    startAsyncRead();
}
