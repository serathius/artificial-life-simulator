#ifndef GENOTYPE_H_
#define GENOTYPE_H_


class Genotype
{
};


class GenotypeMixer
{
private:
  const Genotype& a_;
  const Genotype& b_;

public:
  GenotypeMixer(const Genotype&, const Genotype&);
  const Genotype mix();
};

#endif /* GENOTYPE_H_ */
