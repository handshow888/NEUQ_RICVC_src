#include "SerialCom.cpp"

int main()
{
    SerialPort sp1;
    float send_pitch = -0.13;
    float send_yaw = 0.5;

    sp1.init("/dev/ttyUSB0",115200);
    // sp1.runService();
    // cout << sp1.open() << endl;
    for(int i=1;;i++)
    {
        sp1.write(send_pitch+0.26,send_yaw+1.0,0,0,0);
        cout << "已发送" << dec << i << "次" << endl;
        usleep(100000);
    }
    
    
}
