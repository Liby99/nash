#ifndef SH_FILE_H
#define SH_FILE_H

#include <utility/file.h>
#include <vector>

namespace nash{

  class SHCoefs{
  public:
    int numDegree;
    float * coefs;
  };

  class SHFile : public File{
  public:
    SHFile(int numDegree);
    SHFile(const std::vector<SHCoefs *> samples, int numDegree);

    void save(const std::string &filepath) override;

    void load(const std::string &filepath) override;

    const std::vector<SHCoefs *> &getSamples() const;

    int getNumDegree() const;
  private:
    std::vector<SHCoefs *> samples;
    int numDegree;
  };
}

#endif // SH_FILE_H
