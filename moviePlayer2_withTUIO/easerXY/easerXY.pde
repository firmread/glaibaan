
Easer theEaser;
boolean isFinished;

void setup() {
  size ( 800, 800);
  noStroke();
  i=0;
  
  theEaser = new Easer(78,99,667,504);
}

void draw() {
  background (30);

  isFinished = theEaser.update();
  if (isFinished) {
    println("finished");
    noLoop();
  }
}

