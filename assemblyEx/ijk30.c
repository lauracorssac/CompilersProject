int x;
int K;

int f(int z, int w)
{
  int aux;
  aux = z * w;
  return aux;
}

int mult (int z, int w, int a, int b)
{
  int x;
  x = f(f(z,z),w)+f(a,f(b,b));
  return x;
}

int main()
{
  int y;
  int z;
  x = 2019;
  y = 2;
  z = 2;
  K = mult(y*3, y*4, z*2, z*2);
  return K;
}
