#include "ev3dev.h"
#include "h_crane.h"



class Crain : public CraneCrane
{
private:
    ev3dev::ultrasonic_sensor ultrasonic_q;             //  거리가 달라졌을 때 물건 감지
    ev3dev::sound sound_q;
    ev3dev::touch_sensor touch_q;       
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2), ultrasonic_q(ev3dev::INPUT_1), a(ev3dev::OUTPUT_A)/*목*/, b(ev3dev::OUTPUT_B)/*바디*/, c(ev3dev::OUTPUT_C)
    {
        
    }
    
    int m_speed;
    
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    
    virtual bool get_down()
    {
        return m_down;
    }

    virtual bool get_up()
    {
        return m_up;
    }

    virtual bool get_right()
    {
        return m_right;
    }

    virtual bool get_left()
    {
        return m_left;
    }

    virtual bool get_enter()
    {
        return m_enter;
    }

    virtual bool get_escape()
    {
        return m_escape;
    }

    virtual int  get_speed()
    {
        return 200;
    }

    virtual void set_down(bool val)
    {
        m_down = val;
    }
    
    virtual void set_up(bool val)
    {
        m_up = val;    
    }
    
    virtual void set_right(bool val)
    {
        m_right = val;   
    }
    virtual void set_left(bool val)
    {
        m_left = val; 
    } 
    
    virtual void set_enter(bool val)
    {
        m_enter = val;    
    }
    
    virtual void set_escape(bool val)
    {
        m_escape = val;    
    }
    
    virtual void set_speed(int val)
    {
        m_speed = val;    
    }
    
    void test_code();
    void move_right(int n);
    void move_left(int n);
    void move_down(int n);
    void move_up(int n);
    void open();
    void close();
    void take_object(int n);
    void put_object();
    void example_code();

};


void Crain::example_code()
{ //This function is for example, you should develop your own logics
    while(get_escape() == false)
    {
        set_down(ev3dev::button::down.pressed());
        set_up(ev3dev::button::up.pressed());
        set_right(ev3dev::button::right.pressed());
        set_left(ev3dev::button::left.pressed());
        set_escape(ev3dev::button::back.pressed());
        set_enter(ev3dev::button::enter.pressed());
        
        if(get_up())
        {   
                a.set_speed_sp(-1*get_speed());
                a.run_forever();
        }   
        if(get_down())
        {
                a.set_speed_sp(get_speed());
                a.run_forever();
        }
        if(get_left())
        {
              b.set_speed_sp(-1*get_speed());
              b.run_forever();
        }
        if(get_right())
        {
              b.set_speed_sp(get_speed());
              b.run_forever();
        }
       
       
        if(!(get_up() | get_down() | get_right() | get_left() | get_enter()))
        {
            a.set_speed_sp(0);
            a.run_forever();
            b.set_speed_sp(0);
            b.run_forever();
        }
    }

    a.stop();
    b.stop();
}

void Crain::move_right(int n)       //end 까지 550
{
    //set_right(true);
    b.set_speed_sp(get_speed());
    
    //while(b.position_sp() < n ){
    while(b.position() < n ){
        b.run_forever();}
    
    b.set_stop_action("hold");
    b.stop();
}

void Crain::move_left(int n)
{
    b.set_speed_sp(-1*get_speed());
            
    while(b.position() > n ){
        b.run_forever();}
    //b.set_stop_action("hold");
    b.stop();
}

void Crain::move_down(int n)//180
{

    // a.set_position_sp(n);
    // a.set_speed_sp(get_speed());
    // a.run_to_abs_pos();
    
    
    a.set_speed_sp(get_speed());
    while(a.position() < n){ 
        a.run_forever();}
    a.set_stop_action("hold");
    a.stop();
}

void Crain::move_up(int n) //0
{
    // a.set_position(0);
    // a.set_position_sp(n);
    a.set_speed_sp(-1*get_speed());
    // a.run_to_abs_pos();
    
    while(a.position() > n){ 
        a.run_forever();}
    a.set_stop_action("hold");
    a.stop();
    
}

void Crain::close()
{
    c.set_speed_sp(get_speed());      
    while(c.position() < 0) 
        c.run_forever();
        
    c.set_stop_action("hold");       
    c.stop();
    
}

void Crain::open()
{
    c.set_speed_sp(-1*get_speed());
    while(c.position() > -50)
        c.run_forever();
    //c.set_stop_action("hold");
    c.stop();
    
}


void Crain::take_object(int n)          //n=0이면 open
{
    if(n==0)
        open();
    
    move_down(350);
    sleep(1);
    close();
    sleep(1);
    move_up(0);
}



void Crain::put_object()
{
    move_down(350);
    sleep(1);
    open();
    sleep(1);
    move_up(0);
}


// crain.move_neck(200, 0);
     
//         crain.move_hand(200, 0);
  
//         crain.move_neck(200, 1);
  
//         for(int i = 0; i < 600; i+=10)
//         {
//         crain.move_foot(-1*i, 0);
//         }
  
//         crain.move_hand(100, 1);


// void Crain::move_neck(int pos, int flag)
// {
//     if (flag == 1)
//     {
//         pos *= -1;
//     }
//     b.set_position(0);
//     b.set_position_sp(pos);
//     b.set_speed_sp(get_speed());
//     b.run_to_abs_pos();
// }




/*sensor thresholding!!!!!!*/


void Crain::test_code()
{
    float dis, n = 0;
    int v[100];
    int i = 0;
    
    a.reset();
    b.reset();
    
    
    // // scan
    // b.set_speed_sp(get_speed());
    // b.set_position_sp(0);
    // b.run_to_abs_pos();
    
    while(1)
    {   
        b.reset(); 
        b.set_speed_sp(get_speed());
        // b.set_position_sp(0);
        // b.run_to_abs_pos();
        
        while(b.position() < 550 ){
            
            b.run_forever();
    
            //std::cout << "The value is: " << ultrasonic_q.distance_centimeters() << std::endl;  
            
            
            if(ultrasonic_q.distance_centimeters() > 30 )
                dis = 30;
                
            else
                dis = ultrasonic_q.distance_centimeters();
                
                
            std::cout << "The value is: " << dis << std::endl;      
            
            
            if( -10 > dis - n ){                            // if 물체를 감지하면
                sound_q.speak("Ah", true);
                v[i] = b.position();
                std::cout << "The sensed value is: " << v[i] << std::endl;
                i++;}
            
             n = dis;
        }
    
        b.set_stop_action("hold");
        b.stop(); 
    
        if(i == 3)
            break;
            
        // if( i != 3){
        //     i = 0;
        //     move_left(0);}
        else{   
            i = 0;
            b.reset();
            move_left(-550);}          // 시작 위치로
        
    }
    
    
        
        
        a.reset();    // 현재 neck 위치를 0으로
        b.reset();
        c.reset();      // 닫혀 있는 집게의 위치를 0으로
        
        //move_right(550); 
        //b.reset();
        
        for(int i = 2; i >= 0 ; i--)
        {
            move_left(-550+v[i]);               // i 번째 위치로

            if(i==2)                            // 물건 잡기
                take_object(0);                 
            else
                take_object(1);
    
            move_right(0);                      // End 위치로
    
            put_object();                       // 물건 놓기
            
            b.reset();
        }
        
    a.stop();
    b.stop();

}



int main()
{     
    Crain crain;
    
    // if(crain.get_touch_pressed()==true)
    // {
            //Crain* crain = new Crain;
            
            crain.example_code();
            crain.test_code();
            
          // crain->test_code();
            //delete crain;
    //}
    
}