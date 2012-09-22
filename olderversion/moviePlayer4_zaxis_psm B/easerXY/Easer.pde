
//simple ease-in-out for known start&stop using cosine curve

float i, xN, yN, dx, dy;
int phase =0;
float dist;

class Easer {

  Easer(float _xO, float _yO, float _xT, float _yT ) {
    float xTarget = _xT; //kinda unnecessary
    float yTarget = _yT;
    float xOrig = _xO;
    float yOrig = _yO;

     dx = xTarget-xOrig;
     dy = yTarget-yOrig;
    //dist = sgrt((dx*dx)+(dy*dy));

    i=0;
  }

  boolean update() {
    boolean isDone=false;

    switch (phase) {

    case 0:  //ease in
      xN = 1 - cos(radians (i));
      yN = 1 - cos(radians (i));
      
      fill(255, 0, 0);
      rect( xN*(dx/2.0), yN*(dy/2.0), 50, 50);
      println(xN*(dx/2.0));
      
      i ++;
      if (i>90) phase=1; //at the midpoint now ease out

      break;
    case 1:  //ease out
      i --;
      xN = 1- cos(radians (i));
      yN = 1- cos(radians (i));

      fill(255, 0, 0);
      rect( dx - (xN*(dx/2.0)), dy - (yN*(dy/2.0)), 50, 50);
      println(dx - (xN*(dx/2.0)));
      
      if (i<0) phase=2;
        
      break;
    case 2:
      isDone = true;
    }
    return isDone;
  }
}//end class

