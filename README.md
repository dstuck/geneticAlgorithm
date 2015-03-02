# geneticAlgorithm
Object oriented genetic algorithm code

The beginnings of code to play around with genetic algorithms.

AbstractEcosystem:
  -houses the Environment and Specimen
  -contains main functions to operate alg: Cull, Mate, Mutate, Reproduce
  -helper functions to mess with env and spec
  
AbstractEnvironment:
  -only basic helper functions
  -intended to be almost entirely implementation specific and affect specimen competition
  -ex: maze to run through, larger scale game engine (see mtgAlg)

AbstractSpecimen:
  -contains genes to store solution and fitness to measure weight of solution
  -likely to have implementation spefic functions to compete and calculate fitness and pass on genes
  
Uniwalker Implementation:
  -walkers move right and up to get from bottom left to top right of weighted grid
  -fitness based on sum of weights of points along the path
  -unisolver is a O(N!) recursive solver for the minimal weighted path

TestGeneticAlg reads in an input file and runs the code (only uniwalker for now)
