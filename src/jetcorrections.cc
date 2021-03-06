#include "L1Trigger/UCT2015/interface/jetcorrections.h"


double jetcorr(double ptraw, int ieta, unsigned int pu) {

/*
double calib[]={//npvs less 10 and pu gamma
1.08924, -0.796194, 7.87166,4.70016,
1.23637, -1.53298, 1.92161,8.73352,
1.39727, -1.6164, 1.26115,9.21788,
1.54996, -1.34198, 4.72412,7.5109,
1.28572, -0.838466, 16.5712,4.51977,
1.20415, -0.378877, 22.0251,2.10029,
1.2419, -0.226149, 22.2401,1.19251,
1.22872, -0.276696, 22.7328,1.44926,
1.20016, -0.292763, 21.039,1.60223,
1.16717, -0.269298, 19.8887,1.38555,
1.18129, -0.346614, 18.1018,1.85894,
1.17878, -0.337688, 18.539,1.76453,
1.20447, -0.338309, 19.5434,1.87189,
1.23457, -0.320521, 20.4476,1.70734,
1.26455, -0.293107, 21.9592,1.52638,
1.22106, -0.299124, 22.5949,1.60558,
1.21914, -0.303483, 22.2926,1.63749,
1.29522, -0.817136, 16.6344,4.42117,
1.54566, -0.31911, 4.81533,7.47481,
1.41398, -0.57335, 0.656334,9.02471,
1.18291, -0.45391, 2.86419,8.21465,
1.12678, -0.821578, 7.05472,4.80496,};
*/


        double calib[]={ // no cuts at all
                0.892188, -0.651711, 10.2378, 4.58121,
                1.02586, -1.33642, 4.81479, 9.36397,
                1.27058, -1.50567, 2.07494, 10.4648,
                1.50522, -1.31665, 4.08716, 8.85142,
                1.26861, -0.835476, 16.0302,5.40097,
                1.21747, -0.390929, 21.335, 2.47538,
                1.24958, -0.222715, 21.7479,1.56268,
                1.23016, -0.280122, 22.383,1.79817,
                1.20706, -0.294144, 20.5458,1.92008,
                1.16759, -0.268146, 19.5496,1.74353,
                1.18027, -0.343445, 17.7221,2.23023,
                1.18262, -0.330986, 18.0593,2.13182,
                1.20777, -0.34207, 19.1141, 2.22131,
                1.23128, -0.327868, 20.1695,2.12529,
                1.26521, -0.301663, 21.5901,1.9261,
                1.22042, -0.297534, 22.2525,1.93023,
                1.21491, -0.296532, 22.0371,1.91047,
                1.28441, -0.810513, 15.964,5.24753,
                1.49075, -1.28715, 4.51183,8.75857,
                1.30826, -1.49382, 1.10413,10.3965,
                0.991312, -1.25799, 5.38376,8.87343,
                0.938214, -0.710223, 9.25766,5.20865,};

        /*      double calib[]={ //nocut_puonly
                0.892188, -0.129301, 10.2378,
                1.02586, -0.215941, 4.81479,
                1.27058, -0.263854, 2.07494,
                1.50522, -0.252388, 4.08716,
                1.26861, -0.16307, 16.0302,
                1.21747, -0.0787856, 21.335,
                1.24958, -0.0275552, 21.7479,
                1.23016, -0.0528487, 22.383,
                1.20706, -0.0527709, 20.5458,
                1.16759, -0.0521522, 19.5496,
                1.18027, -0.0668484, 17.7221,
                1.18262, -0.064321, 18.0593,
                1.20777, -0.0640411, 19.1141,
                1.23128, -0.0588989, 20.1695,
                1.26521, -0.0598296, 21.5901,
                1.22042, -0.055804, 22.2525,
                1.21491, -0.05783, 22.0371,
                1.28441, -0.162218, 15.964,
                1.49075, -0.218651, 4.51183,
                1.30826, -0.264765, 1.10413,
                0.991312, -0.199525, 5.38376,
                0.938214, -0.107628, 9.25766,};
         */

        /*      double calib[] = {  // calib_pu UIC! npvsless10_puonly
                1.08924, -0.258638, 7.87166,
                1.23637, -0.490655, 1.92161,
                1.39727, -0.523398, 1.26115,
                1.54996, -0.439019, 4.72412,
                1.28572, -0.275938, 16.5712,
                1.20415, -0.114389, 22.0251,
                1.2419,  -0.0773385, 22.2401,
                1.22872, -0.0934096, 22.7328,
                1.20016, -0.091572, 21.039,
                1.16717, -0.0979654, 19.8887,
                1.18129, -0.116205, 18.1018,
                1.17878, -0.117217, 18.539,
                1.20447, -0.103698, 19.5434,
                1.23457, -0.104685, 20.4476,
                1.26455, -0.101697, 21.9592,
                1.22106, -0.0981272, 22.5949,
                1.21914, -0.0991646, 22.2926,
                1.29522, -0.270886, 16.6344,
                1.54566, -0.406463, 4.81533,
                1.41398, -0.507259, 0.656334,
                1.18291, -0.475049, 2.86419,
                1.12678, -0.266153, 7.05472,};
         */      
        /*              double calib[] = {  // calib_pu UIC!
                        1.08924, 0, 7.87166,
                        1.23637, 0, 1.92161,
                        1.39727, 0, 1.26115,
                        1.54996, 0, 4.72412,
                        1.28572, 0, 16.5712,
                        1.20415, 0, 22.0251,
                        1.2419,  0, 22.2401,
                        1.22872, 0, 22.7328,
                        1.20016, 0, 21.039,
                        1.16717, 0, 19.8887,
                        1.18129, 0, 18.1018,
                        1.17878, 0, 18.539,
                        1.20447, 0, 19.5434,
                        1.23457, 0, 20.4476,
                        1.26455, 0, 21.9592,
                        1.22106, 0, 22.5949,
                        1.21914, 0, 22.2926,
                        1.29522, 0, 16.6344,
                        1.54566, 0, 4.81533,
                        1.41398, 0, 0.656334,
                        1.18291, 0, 2.86419,
                        1.12678, 0, 7.05472,}; 
         */
        /*      double calib[] = {  // calib_pu UIC!    
                0.892188, 0, 10.2378,
                1.02586, 0, 4.81479,
                1.27058, 0, 2.07494,
                1.50522, 0, 4.08716,
                1.26861, 0, 16.0302,
                1.21747, 0, 21.335,
                1.24958, 0, 21.7479,
                1.23016, 0, 22.383,
                1.20706, 0, 20.5458,
                1.16759, 0, 19.5496,
                1.18027, 0, 17.7221,
                1.18262, 0, 18.0593,
                1.20777, 0, 19.1141,
                1.23128, 0, 20.1695,
                1.26521, 0, 21.5901,
                1.22042, 0, 22.2525,
                1.21491, 0, 22.0371,
                1.28441, 0, 15.964,
                1.49075, 0, 4.51183,
                1.30826, 0, 1.10413,
                0.991312, 0, 5.38376,
                0.938214, 0, 9.25766,   }; 
         */
        //==============================================

        double alpha = calib[3*ieta + 0];
        double beta  = calib[3*ieta + 1];
        double gamma = calib[3*ieta + 2];
        double delta = calib[4*ieta + 3];       

        double pt =  alpha * ptraw + beta * pu + gamma + delta;
        
//      double pt =  alpha * ptraw + beta * pu + gamma;
        return pt;
}

double jetcorrUIC(double ptraw, int ieta, unsigned int pu) {
/*
double calib[]={//npvs less 10 and pu gamma
1.08924, -0.796194, 7.87166,4.70016,
1.23637, -1.53298, 1.92161,8.73352,
1.39727, -1.6164, 1.26115,9.21788,
1.54996, -1.34198, 4.72412,7.5109,
1.28572, -0.838466, 16.5712,4.51977,
1.20415, -0.378877, 22.0251,2.10029,
1.2419, -0.226149, 22.2401,1.19251,
1.22872, -0.276696, 22.7328,1.44926,
1.20016, -0.292763, 21.039,1.60223,
1.16717, -0.269298, 19.8887,1.38555,
1.18129, -0.346614, 18.1018,1.85894,
1.17878, -0.337688, 18.539,1.76453,
1.20447, -0.338309, 19.5434,1.87189,
1.23457, -0.320521, 20.4476,1.70734,
1.26455, -0.293107, 21.9592,1.52638,
1.22106, -0.299124, 22.5949,1.60558,
1.21914, -0.303483, 22.2926,1.63749,
1.29522, -0.817136, 16.6344,4.42117,
1.54566, -0.31911, 4.81533,7.47481,
1.41398, -0.57335, 0.656334,9.02471,
1.18291, -0.45391, 2.86419,8.21465,
1.12678, -0.821578, 7.05472,4.80496,};
*/


        double calib[]={ // no cuts at all
                0.892188, -0.651711, 10.2378, 4.58121,
                1.02586, -1.33642, 4.81479, 9.36397,
                1.27058, -1.50567, 2.07494, 10.4648,
                1.50522, -1.31665, 4.08716, 8.85142,
                1.26861, -0.835476, 16.0302,5.40097,
                1.21747, -0.390929, 21.335, 2.47538,
                1.24958, -0.222715, 21.7479,1.56268,
                1.23016, -0.280122, 22.383,1.79817,
                1.20706, -0.294144, 20.5458,1.92008,
                1.16759, -0.268146, 19.5496,1.74353,
                1.18027, -0.343445, 17.7221,2.23023,
                1.18262, -0.330986, 18.0593,2.13182,
                1.20777, -0.34207, 19.1141, 2.22131,
                1.23128, -0.327868, 20.1695,2.12529,
                1.26521, -0.301663, 21.5901,1.9261,
                1.22042, -0.297534, 22.2525,1.93023,
                1.21491, -0.296532, 22.0371,1.91047,
                1.28441, -0.810513, 15.964,5.24753,
                1.49075, -1.28715, 4.51183,8.75857,
                1.30826, -1.49382, 1.10413,10.3965,
                0.991312, -1.25799, 5.38376,8.87343,
                0.938214, -0.710223, 9.25766,5.20865,};


/*      double calib[]={ //nocut_puonly
                0.892188, -0.129301, 10.2378,
                1.02586, -0.215941, 4.81479,
                1.27058, -0.263854, 2.07494,
                1.50522, -0.252388, 4.08716,
                1.26861, -0.16307, 16.0302,
                1.21747, -0.0787856, 21.335,
                1.24958, -0.0275552, 21.7479,
                1.23016, -0.0528487, 22.383,
                1.20706, -0.0527709, 20.5458,
                1.16759, -0.0521522, 19.5496,
                1.18027, -0.0668484, 17.7221,
                1.18262, -0.064321, 18.0593,
                1.20777, -0.0640411, 19.1141,
                1.23128, -0.0588989, 20.1695,
                1.26521, -0.0598296, 21.5901,
                1.22042, -0.055804, 22.2525,
                1.21491, -0.05783, 22.0371,
                1.28441, -0.162218, 15.964,
                1.49075, -0.218651, 4.51183,
                1.30826, -0.264765, 1.10413,
                0.991312, -0.199525, 5.38376,
                0.938214, -0.107628, 9.25766,};

*/

        /*double calib[] = {  // calib_pu UIC! npvsless10_puonly
          1.08924, -0.258638, 7.87166,
          1.23637, -0.490655, 1.92161,
          1.39727, -0.523398, 1.26115,
          1.54996, -0.439019, 4.72412,
          1.28572, -0.275938, 16.5712,
          1.20415, -0.114389, 22.0251,
          1.2419,  -0.0773385, 22.2401,
          1.22872, -0.0934096, 22.7328,
          1.20016, -0.091572, 21.039,
          1.16717, -0.0979654, 19.8887,
          1.18129, -0.116205, 18.1018,
          1.17878, -0.117217, 18.539,
          1.20447, -0.103698, 19.5434,
          1.23457, -0.104685, 20.4476,
          1.26455, -0.101697, 21.9592,
          1.22106, -0.0981272, 22.5949,
          1.21914, -0.0991646, 22.2926,
          1.29522, -0.270886, 16.6344,
          1.54566, -0.406463, 4.81533,
          1.41398, -0.507259, 0.656334,
          1.18291, -0.475049, 2.86419,
          1.12678, -0.266153, 7.05472,};
         */ 
        /*      double calib[] = {  // calib_pu UIC!    
                0.892188, 0, 10.2378,
                1.02586, 0, 4.81479,
                1.27058, 0, 2.07494,
                1.50522, 0, 4.08716,
                1.26861, 0, 16.0302,
                1.21747, 0, 21.335,
                1.24958, 0, 21.7479,
                1.23016, 0, 22.383,
                1.20706, 0, 20.5458,
                1.16759, 0, 19.5496,
                1.18027, 0, 17.7221,
                1.18262, 0, 18.0593,
                1.20777, 0, 19.1141,
                1.23128, 0, 20.1695,
                1.26521, 0, 21.5901,
                1.22042, 0, 22.2525,
                1.21491, 0, 22.0371,
                1.28441, 0, 15.964,
                1.49075, 0, 4.51183,
                1.30826, 0, 1.10413,
                0.991312, 0, 5.38376,
                0.938214, 0, 9.25766,   }; 
         */
        //==============================================

        // std::cout << " JetCorr: " << ptraw << " " << ieta << " " << pu << std::endl;
        double alpha = calib[4*ieta + 0];
        double beta  = calib[4*ieta + 1];
        double gamma = calib[4*ieta + 2];
        double delta = calib[4*ieta + 3];       

        double pt =  alpha * ptraw + beta * pu + gamma + delta;
        return pt;
}

