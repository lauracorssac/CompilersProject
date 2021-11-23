int f(int a, int b, int c, int d, int e, int af, int g, int h, int sa, int sb, int sc, int sd, int se, int saf, int sg, int sh) {
    
    return a + b + c + d + e + af + g + h + sa + sb + sc + sd + se + saf + sg + sh;
    
}

int main() {
    int x;
    int y;
    x = 10;
    y = 20;
    y = x + f(x, y, x, y, x, y, x, x, x, y, x, y, x, y, x, x);
    return 0;
}

