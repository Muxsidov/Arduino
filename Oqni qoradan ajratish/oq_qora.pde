import processing.serial.*;
Serial port;
float nextValue = 0, minimum = 1023, maximum = 0;
int sizeRect = 500, cnt = 0;

String s, min, max, oq;

FloatList oscill;

void setup()
{
fullScreen();
port = new Serial(this, "COM3", 9600);
port.bufferUntil('\n');
oscill = new FloatList();
oq = new String("oq");
textSize(150);

}

void draw()
{
  background(0);
  text(oq, displayWidth / 2, displayHeight / 2);
}

void serialEvent (Serial port)
{
try {
  nextValue = float(port.readStringUntil('\n'));
  if(cnt > 100)
  {
    if (nextValue > maximum) maximum = nextValue;
    if (nextValue < minimum) minimum = nextValue;
  }
  s= "current: "+int(nextValue);
  min = "min: "+int(minimum);
  max = "max: "+int(maximum);
  if (int(nextValue) > 400)
  {
    oq = "qora";
  }
  else
  {
    oq = "oq";
  }
  cnt++;
  
  if (!(oscill.size()<sizeRect)) {
    oscill.remove(0);
   }

  oscill.append(nextValue);
} catch (Exception e) {
  println("Connection...");
}

}

void mouseClicked()
{
  minimum = 1023;
  maximum = 0;
}

void stop() {
port.clear();
port.stop();
}
