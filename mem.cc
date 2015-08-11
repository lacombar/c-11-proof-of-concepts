class Foo
{
	public:
	Foo() :
		p_(new int[256])
	{
	}
	private:
	int * p_;
};

int main(int argc, char *argv[])
{
	Foo f;

	return 0;
}
