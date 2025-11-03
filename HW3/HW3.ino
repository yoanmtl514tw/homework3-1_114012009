const int RledPin =9;
const int GledPin =10;
const int BledPin =11;
const int buttonPin = 2;

int button_state =0;

bool button_pressed = false;
unsigned long pressing_time = 0;
const int long_press_interval = 1000;

//Change color short click - Variable
int light_num = 0;
int r_light_color = 0;
int g_light_color = 0;
int b_light_color = 0;

//blink mode - variable
int r_current_color =0;
int g_current_color =0;
int b_current_color =0;
int current_mode =0;
unsigned long blink_timer = 0;
const int blink_interval = 200;
bool blink_on = true;

//fade mode - variable
const int fade_amount = 2;
int fade_direction =1;


void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(RledPin, OUTPUT);
  pinMode(GledPin, OUTPUT);
  pinMode(BledPin, OUTPUT);
  //Serial.begin(9600);
}

void loop()
{
  check_button();
  update_led_color();
  set_rgb_color(r_current_color,g_current_color,b_current_color);
}


//======FUNCTION=====

//Set the RGB LED COLOR
void set_rgb_color(int r, int g, int b)
{
  analogWrite(RledPin, r);
  analogWrite(GledPin, g);
  analogWrite(BledPin, b);
}

//CHECK IF SHORT OR LONG PRESS
void check_button()
{
  button_state = digitalRead(buttonPin);

  if(button_state == LOW && !button_pressed)
  {
    pressing_time = millis();
    button_pressed = true;
  }
  if(button_state == HIGH && button_pressed)
  {
    delay(20);
    unsigned long current_time = millis();
    if(current_time - pressing_time < long_press_interval)
    {
      //short click
      //Serial.println("short click");
      change_led_color();
    }
    else
    {
      //long press
      //Serial.println("long click");
      change_mode();
    }

    button_pressed = false;
  }
}

//CHANGING THE LED COLOR
void change_led_color()
{
  light_num = light_num +1;

  if(light_num >= 5)
  {
    light_num =0;
  }
  if(light_num ==0)
  {
    r_light_color = 0;
    g_light_color = 0;
    b_light_color = 0;
  }
  if(light_num ==1)
  {
    r_light_color = 0;
    g_light_color = 255;
    b_light_color = 255;
  }
  if(light_num ==2)
  {
    r_light_color = 255;
    g_light_color = 0;
    b_light_color = 255;
  }
  if(light_num ==3)
  {
    r_light_color = 255;
    g_light_color = 255;
    b_light_color = 0;
  }
  if(light_num ==4)
  {
    r_light_color = 0;
    g_light_color = 0;
    b_light_color = 255;
  }
}

//CHANGING THE MODE
void change_mode ()
{
  current_mode = current_mode +1;
  if(current_mode >=3)
  {
    current_mode = 0;
  }
  if(current_mode == 1)
  {
    blink_timer = 0;
    blink_on = true;
  }
  if(current_mode ==2)
  {
    fade_direction =1;
  }
}

void update_led_color()
{
  if(current_mode == 0)
  {
    r_current_color = r_light_color;
    g_current_color = g_light_color;
    b_current_color = b_light_color;
  }
  else if(current_mode ==1)
  {
    //blink mode
    unsigned long current_time = millis();
    if(current_time - blink_timer > blink_interval)
    {
      blink_on = !blink_on;
      blink_timer = current_time;
    }

    if(blink_on)
    {
      r_current_color = r_light_color;
      g_current_color = g_light_color;
      b_current_color = b_light_color;
    }
    else
    {
      r_current_color = 255;
      g_current_color = 255;
      b_current_color = 255;
    }
  }
  else if(current_mode == 2)
  {
    bool negative_dir = false;

    if(r_light_color == 0)
    {
      r_current_color = r_current_color + fade_direction * fade_amount;
      if(r_current_color > (255 - r_light_color)||(r_current_color <0))
      {
        negative_dir = true;
      }
      if(r_current_color < 0) r_current_color =0;
      if(r_current_color >255) r_current_color = 255;
    }

    if(g_light_color == 0)
    {
      g_current_color = g_current_color + fade_direction * fade_amount;
      if(g_current_color > (255 - g_light_color)||(g_current_color <0))
      {
        negative_dir = true;
      }
      if(g_current_color < 0) g_current_color =0;
      if(g_current_color >255) g_current_color = 255;
    }

    if(b_light_color == 0)
    {
      b_current_color = b_current_color + fade_direction * fade_amount;
      if(b_current_color > (255 - b_light_color)||(b_current_color <0))
      {
        negative_dir = true;
      }
      if(b_current_color < 0) b_current_color =0;
      if(b_current_color >255) b_current_color = 255;
    }
    if(negative_dir)
    {
      fade_direction = -fade_direction;
    }

    delay(10);
  }
}

//


