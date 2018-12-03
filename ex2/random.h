static int seed = 3;

void setSeed(int s)
{
    int last;

    if(s == 0)
        s = 2;

    for(unsigned int i = (unsigned int)s + 1; i > last; i += i)
    {
        last = i;
    }

    seed = last;
}


void randAnyInt()
{

}
