extern "C" void doublebuf(unsigned char* buf, int size)
{
 for (int i=0; i<size; i++)
    buf[i] = 2*buf[i];
}