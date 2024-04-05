class counterType
{
  private:
    int counter;

  public:
    counterType(int counter = 0);

    void setCounter(int);
    int getCounter();
    void incrementCounter();
    void decrementCounter();
    void print();
};
