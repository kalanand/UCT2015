// $Id: Histograms.h,v 1.1 2012/11/15 21:09:46 aosorio Exp $
#ifndef TEMP_HISTOGRAMS_H 
#define TEMP_HISTOGRAMS_H 1

// Include files
#include <TH1F.h>
#include <TH2F.h>
#include <map>

/** @class Histograms Histograms.h Temp/Histograms.h
 *  
 *
 *  @author Andres Osorio
 *  @date   2012-11-14
 */

class Histograms {
 public: 
  /// Standard constructor
  Histograms( ); 
  
  virtual ~Histograms( ); ///< Destructor
  
  std::map<std::string, TH1F*> m_histograms1D;
  std::map<std::string, TH2F*> m_histograms2D;
  
 protected:
  
 private:
  


};
#endif // TEMP_HISTOGRAMS_H
