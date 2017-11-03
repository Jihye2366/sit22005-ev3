#include <iostream>
#include <stdlib.h>
#include "ev3dev.h"
#include "h_crane.h"

class Crain : public CraneCrane
{
private:
    ev3dev::touch_sensor touch_q;
    ev3dev::ultrasonic_sensor ultrasonic_q;
    ev3dev::sound sound_q;
    ev3dev::motor a;
    ev3dev::motor b; 
    ev3dev::motor c;
    
// a: neck, b: axis, c: pick
public:
    // Hardware Configuration
    Crain():m_speed(0), touch_q(ev3dev::INPUT_2), ultrasonic_q(ev3dev::INPUT_1), a(ev3dev::OUTPUT_A), b(ev3dev::OUTPUT_B), c(ev3dev::OUTPUT_C)
    {
        
    }
    
    int m_speed;
    bool get_touch_pressed()
    {
        return touch_q.is_pressed();
    }
    
    bool get_sensed()
    {
        return ultrasonic_q.distance_inches();
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
        return 100;
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
    
public:
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
               b.set_speed_sp(get_speed());
               b.run_forever();
        }
        if(get_right())
        {
               b.set_speed_sp(-1* get_speed());
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

void Crain::move_axis(int n)       //end 까지 550?
{
    // while ((b.position_sp() <=20) || (b.position_sp() >=20)) {
        b.set_speed_sp(get_speed());
        b.set_position_sp(n);
        b.run_to_abs_pos();
        b.set_stop_action("hold");
        b.stop();
    // }
}


void Crain::move_neck(int n) // 350 정도, max 670
{
    // while ((a.position_sp() <=20) || (a.position_sp() >=20)) {
        a.set_speed_sp(get_speed());
        a.set_position_sp(n);
        a.run_to_abs_pos();
        a.set_stop_action("hold");
        a.stop();
    // }
}

void Crain::pick(int n) // 0부터 100
{
    // while ((c.position_sp() <=20) || (c.position_sp() >=20)) {
        c.set_speed_sp(get_speed());
        c.set_position_sp(0);
        c.run_to_abs_pos();
        c.set_stop_action("hold");
        c.stop();
    // }
}

/*
void Crain::take_object(int n)          //n=0이면 open
{
    if(n==0)
        open();
    
    move_down(200);
    close();
    move_up(0);
}



void Crain::put_object()
{
    move_down(200);
    open();
    move_up(0);
}
*/

void Crain::test_code()
{
    float n;
    int v[3] = {100,230,400};
    //int i = 0;
    
    a.reset();
    b.reset();
    
    move_neck(350);
    sleep(0.5);
    
    
    // scan
    
        // set_right(true);
        // b.set_speed_sp(get_speed());
        
        // while(b.position() < /*v[i]*/ 500)
        // {
              //b.reset();
        //      b.run_forever();
            
        //     n = ultrasonic_q.distance_centimeters();  
            
        //     if(n > ultrasonic_q.distance_centimeters()){                            // if 물체를 감지하면
        //          sound_q.speak("Ah", true);
        //          v[i] = b.position_sp();
        //          i++;}
            
        //     if(b.position() >= 550)            // End 위치에 도달할 때까지
        //      {
        //     if(i == 2){
        //      //b.set_stop_action(hold);
        //        b.stop;
        //         break;
        //      }
            
        //     else{   
        //         i = 0;
        //         b.run_to_abs_pos(0);}          // 시작 위치로
        //     }  
        // }
        
        // a.reset();    // 현재 neck 위치를 0으로
        // b.reset();
        // c.reset();      // 닫혀 있는 집게의 위치를 0으로
        
    /*    
    for(int i = 2; i >= 0 ; i--)
    {
            
        move_right(550);                   // End 위치로(test)
        sleep(0.5);
            
        b.reset();
            
        move_left(v[i]);                   // i 번째 위치로

        // if(i==0)                            // 물건 잡기
        //     take_object(0);                 
        // else
        //     take_object(1);
                //move_right(550);                    // End 위치로
                //put_object();                       // 물건 놓기
        
        //b.reset();
    }
        
        // a.stop();
        // b.stop();
    */
}

int main()
{     
    Crain crain;
    while(true){
        crain.example_code();
        if(crain.get_touch_pressed()==true){
            // test_code* instance = new test_code;
            // crain.example_code();
            crain.test_code();
            // delete test_code;
        }
    }
}