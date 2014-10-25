//takes the input (i) with a range between a-b and linearly maps it to the range c-d
//pre: c > d
float tMap(float i, float a, float b, float c, float d) {
  float i = map(i,a,b,c,d);
  //uncomment portions of code if c > d, otherwise leave them out for speed
  //if (c < d) {
    if (i < c)
      i = c;
    else if (i > d)
      i = d;
  /*} 
  else {
    if (i > c)
      i = c;
    else if (i < d)
      i = d;
  }*/
  return i;
}

//takes the input (i) with a range between a-b and linearly maps it to the range c-d
float truncateMap(float i, float a, float b, float c, float d) {
  i = map(i,a,b,c,d);
  //uncomment portions of code if c > d, otherwise leave them out for speed
  if (c < d) {
    if (i < c)
      i = c;
    else if (i > d)
      i = d;
  } 
  else {
    if (i > c)
      i = c;
    else if (i < d)
      i = d;
  /
  return i;
}
