#ifndef coord_h
#define coord_h

class DOT
{
private:
		int x;
		int y;

public:
		DOT(int,int);
		DOT();
		void SetCoord(int, int);
		int GetXCoord();
		int GetYCoord();
};

DOT::DOT(int x1, int y1)
{
	x= x1;
	y= y1;
}

DOT::DOT()
{
	x=1;
	y=1;
}

void DOT::SetCoord(int x1, int y1)
{
	x= x1;
	y= y1;
	return;
}

int DOT::GetXCoord()
{ 
	return(x);
}

int DOT::GetYCoord()
{ 
	return(y);
}

#endif
