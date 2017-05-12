#pragma once

class Serial {

public:
  Serial(const char *bytes, const unsigned int len);
  ~Serial();
  char *get_bytes() const;
  unsigned int get_len() const;

private:
  char *bytes;
  const unsigned int len;

};
