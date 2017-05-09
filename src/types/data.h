#pragma once



class Data {

public:
  static const int MAX_SIZE;

  Data(char *bytes, unsigned int len);
  ~Data();
  void preview();
  void serialize(char **bytes, int *len);
  static Data parse(char *bytes, int len);

private:
  char *bytes;
  unsigned int len;

};
