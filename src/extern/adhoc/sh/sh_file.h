#ifndef SH_FILE_H
#define SH_FILE_H

#include "adhoc/sh/sh_coefs.h"
#include "utility/file.h"
#include <vector>

namespace nash {
  class SHFile : public File {
  public:
    SHFile(int numDegree);
    SHFile(const std::vector<SHCoefs *> coefsList, int numDegree);

    void save(const std::string &filepath) override;

    void load(const std::string &filepath) override;

    const std::vector<SHCoefs *> &getCoefsList() const;

    int getNumDegree() const;

  private:
    std::vector<SHCoefs *> coefsList;
    int numDegree;
  };
}

#endif // SH_FILE_H
