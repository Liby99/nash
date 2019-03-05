#include <adhoc/sh/sh_file.h>
#include <iostream>
#include <stdexcept>
#include <stdio.h>
#include <string.h>
#include <utility/path.h>

using namespace nash;

SHFile::SHFile(int numDegree) : numDegree(numDegree) {}

SHFile::SHFile(const std::vector<SHCoefs *> coefsList, int numDegree)
    : coefsList(coefsList), numDegree(numDegree) {}

void SHFile::save(const std::string &filepath) {
  FILE *pFile = fopen(filepath.c_str(), "wb");
  if (pFile == nullptr) {
    throw std::runtime_error("Cannot load file " + filepath);
  }
  int vertCount = coefsList.size();
  int coefsCount = numDegree * numDegree;

  // ((1 + 1) (header) + vert * coefs) * 4 bytes
  int bufSize = (2 + vertCount * coefsCount) * 4;
  char *buf = (char *)malloc(bufSize);

  // write header
  memcpy(buf + 0, &vertCount, sizeof(int));
  memcpy(buf + 4, &numDegree, sizeof(int));

  // write content
  for (int i = 0; i < vertCount; i++) {
    const SHCoefs *currSample = coefsList[i];

    int srcSize = currSample->numDegree * currSample->numDegree * sizeof(float);
    int distSize = coefsCount * sizeof(float);

    float *coefs = (float *)malloc(distSize);
    memset(coefs, 0, distSize);
    memcpy(coefs, currSample->coefs, std::min(srcSize, distSize));

    memcpy(buf + 8 + i * distSize, coefs, distSize);
    delete coefs;
  }

  fwrite(buf, 1, bufSize, pFile);

  delete buf;
  fclose(pFile);
}

void SHFile::load(const std::string &filepath) {
  FILE *pFile = fopen(filepath.c_str(), "rb");
  if (pFile == nullptr) {
    throw std::runtime_error("Cannot load file " + filepath);
  }

  // Get the file size
  fseek(pFile, 0L, SEEK_END);
  int fileSize = ftell(pFile);
  rewind(pFile);

  // Create buffer for the whole file.
  char *buf = (char *)malloc(fileSize);
  fread(buf, 1, fileSize, pFile);

  // The file is no longer needed
  fclose(pFile);

  // parse header
  int vertCount = ((int *)buf)[0];
  if (numDegree <= 0) {
    numDegree = ((int *)buf)[1];
  }
  int coefsSize = numDegree * numDegree * sizeof(float);
  int actualSize = ((int *)buf)[1] * ((int *)buf)[1] * sizeof(float);

  // ((1 + 1) (header) + vert * coefs) * 4 bytes
  coefsList.clear();
  coefsList.resize(vertCount);

  // parse content
  for (int i = 0; i < vertCount; i++) {
    float *coefs = (float *)malloc(coefsSize);
    memset(coefs, 0, coefsSize);
    memcpy(coefs, buf + 8 + i * actualSize, std::min(actualSize, coefsSize));

    // Create Object
    SHCoefs *currCoefs = new SHCoefs;
    currCoefs->numDegree = numDegree;
    currCoefs->coefs = coefs;

    coefsList[i] = currCoefs;
  }

  delete buf;
}

const std::vector<SHCoefs *> &SHFile::getCoefsList() const { return coefsList; }

int SHFile::getNumDegree() const { return numDegree; }

void SHFile::print() const {
  std::cout << coefsList.size() << " " << numDegree << std::endl;
  for (int i = 0; i < coefsList.size(); i++) {
    for (int l = 0; l < numDegree; l++) {
      for (int m = -l; m <= l; m++) {
        std::cout << coefsList[i]->get(l, m) << " ";
      }
    }
    std::cout << std::endl;
  }
}
