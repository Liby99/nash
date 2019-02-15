#include <stdio.h>
#include <stdexcept>
#include <adhoc/sh/sh_file.h>
#include <utility/path.h>

using namespace nash;

SHFile::SHFile(int numDegree) : numDegree(numDegree){ }

SHFile::SHFile(const std::vector<SHCoefs *> samples, int numDegree) :
  samples(samples),
  numDegree(numDegree){ }

void SHFile::save(const std::string &filepath) {
  const std::string absPath = Path::getAbsolutePathTo(filepath);
  FILE * pFile = fopen(absPath.c_str(), "wb");
  if (pFile == nullptr) {
    throw std::runtime_error("Cannot load file " + absPath);
  }
  int vertCount = samples.size();
  int coefsCount = numDegree * numDegree;

  // ((1 + 1) (header) + vert * coefs) * 4 bytes
  int bufSize = (2 + vertCount * coefsCount) * 4;
  char * buf = (char *)malloc(bufSize);

  // write header
  memcpy(buf + 0, &vertCount, sizeof(int));
  memcpy(buf + 4, &numDegree, sizeof(int));

  // write content
  for(int i = 0; i < vertCount; i ++){
    const SHCoefs * currSample = samples[i];

    int srcSize = currSample->numDegree * currSample->numDegree * sizeof(float);
    int distSize = coefsCount * sizeof(float);

    float * coefs = (float*)malloc(distSize);
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
  const std::string absPath = Path::getAbsolutePathTo(filepath);
  FILE * pFile = fopen(absPath.c_str(), "rb");
  if (pFile == nullptr) {
    throw std::runtime_error("Cannot load file " + absPath);
  }

  // Get the file size
  fseek(pFile, 0L, SEEK_END);
  int fileSize = ftell(pFile);
  rewind(pFile);

  // Create buffer for the whole file.
  char * buf = (char*)malloc(fileSize);
  fread(buf, 1, fileSize, pFile);

  // The file is no longer needed
  fclose(pFile);

  // parse header
  int vertCount = ((int*)buf)[0];
  if(numDegree <=0) {
    numDegree = ((int *) buf)[1];
  }
  int coefsSize = numDegree * numDegree * sizeof(float);
  int actualSize = ((int *) buf)[1] * ((int *) buf)[1] * sizeof(float);


      // ((1 + 1) (header) + vert * coefs) * 4 bytes
  samples.clear();
  samples.resize(vertCount);

  // parse content
  for(int i = 0; i < vertCount; i ++){
    float * coefs = (float*)malloc(coefsSize);
    memset(coefs, 0, coefsSize);
    memcpy(coefs, buf + 8 + i * actualSize, coefsSize);

    // Create Object
    SHCoefs * currCoefs = new SHCoefs;
    currCoefs->numDegree = numDegree;
    currCoefs->coefs = coefs;

    samples[i] = currCoefs;
  }

  delete buf;
}

const std::vector<SHCoefs *> &SHFile::getSamples() const {
  return samples;
}

int SHFile::getNumDegree() const {
  return numDegree;
}

