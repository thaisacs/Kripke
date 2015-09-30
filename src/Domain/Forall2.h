//AUTOGENERATED BY genForallN.py
  
#ifndef __DOMAIN_FORALL2_H__
#define __DOMAIN_FORALL2_H__

#include<RAJA/RAJA.hxx>


    template<typename POLICY, typename TI, typename TJ, typename BODY>
    inline void forall2(TI const &is_i, TJ const &is_j, BODY const &body){
      typedef typename POLICY::LoopOrder L;
      forall2<POLICY, TI, TJ, BODY>(L(), is_i, is_j, body);
    }

    template<typename LOOP_ORDER, typename POL_I, typename POL_J>
    struct ForallPolicy2 {
      typedef LOOP_ORDER LoopOrder;
      typedef POL_I PolicyI;
      typedef POL_J PolicyJ;
    };


/******************************************************************
 *  Implementation for permutations of forall2()
 ******************************************************************/

      template<typename POLICY, typename TI, typename TJ, typename BODY>
      inline void forall2(PERM_IJ, TI const &is_i, TJ const &is_j, BODY const &body){
        RAJA::forall<typename POLICY::PolicyI>(is_i, [=](int i){
          RAJA::forall<typename POLICY::PolicyJ>(is_j, [=](int j){
            body(i, j);
          });
        });
      }

      template<typename POLICY, typename TI, typename TJ, typename BODY>
      inline void forall2(PERM_JI, TI const &is_i, TJ const &is_j, BODY const &body){
        RAJA::forall<typename POLICY::PolicyJ>(is_j, [=](int j){
          RAJA::forall<typename POLICY::PolicyI>(is_i, [=](int i){
            body(i, j);
          });
        });
      }


  
#endif

