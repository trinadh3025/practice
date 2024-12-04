#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

/**
 * The PVRMumbai is Target cinema. the domain-specific interface used by the client code.
 */
class PVRMumbai {
 public:
  virtual ~PVRMumbai() = default;

  virtual std::string PlayRequest() const {
    return "PVR MUMBAI: The default language is Hindi";
  }
};

/**
 * The TeluguMovie(Adaptee) contains some useful behavior(translation), but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
class TeluguMovie {
 public:
  std::string DubRequest() const {
    return ".gniyalp si ullaMareeVarahiraH";
  }
};

/**
 * The Dubbing(Adapter) makes the TeluguMovie(Adaptee)'s interface compatible with the PVRMumbai(Target)'s
 * interface.
 */
class Dubbing : public PVRMumbai {
 private:
  TeluguMovie *telugumovie_;

 public:
  Dubbing(TeluguMovie *telugumovie) : telugumovie_(telugumovie) {}
  std::string PlayRequest() const override {
    std::string to_reverse = this->telugumovie_->DubRequest();
    std::reverse(to_reverse.begin(), to_reverse.end());
    return "Dubbing: (TRANSLATED) " + to_reverse;
  }
};

/**
 * The PlayMovie(client code) supports all classes that follow the PVRMumbai interface.
 */
void PlayMovie(const PVRMumbai *target) {
  std::cout << target->PlayRequest();
}

int main() {
  std::cout << "PVR_Mumbai: I can play just fine with Hindi language movies\n";
  PVRMumbai *pvrMumbai = new PVRMumbai;
  PlayMovie(pvrMumbai);
  std::cout << "\n\n";
  TeluguMovie *t_movie = new TeluguMovie;
  std::cout << "Client: The TeluguMovie needs translation. See, I don't understand it:\n";
  std::cout << "TeluguMovie: " << t_movie->DubRequest();
  std::cout << "\n\n";
  std::cout << "Client: But I can play with Dubbing:\n";
  Dubbing *dubMovie = new Dubbing(t_movie);
  PlayMovie(dubMovie);
  std::cout << "\n";

  delete pvrMumbai;
  delete t_movie;
  delete dubMovie;

  return 0;
}
