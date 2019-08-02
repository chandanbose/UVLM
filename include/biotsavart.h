#pragma once

#include "EigenInclude.h"
#include "types.h"
#include "mapping.h"
#include "debugutils.h"

#include <limits>
#include <math.h>
#include <cmath>

// #define VORTEX_RADIUS 1e-5
#define VORTEX_RADIUS 1.e-6
#define VORTEX_RADIUS_SQ 1e-4
#define EPSILON_VORTEX 1e-10
#define Nvert 4

// Declaration for parallel computing
#pragma omp declare reduction (sum_Vector3 : UVLM::Types::Vector3 : omp_out += omp_in) initializer(omp_priv = UVLM::Types::zeroVector3())

namespace UVLM
{
    namespace BiotSavart
    {
        // DECLARATIONS
        template <typename t_zeta,
                  typename t_gamma,
                  typename t_tsurface,
                  typename t_uout,
                  typename t_normals>
        void multisurface
        (
            const t_zeta&       zeta,
            const t_gamma&      gamma,
            const t_tsurface&   target_surface,
            t_uout&             uout,
            // const UVLM::Types::IntPair& dimensions,
            const bool&         image_method = false,
            const t_normals&    normal = NULL,
            // const bool&         horseshoe = false,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );

        template <typename t_zeta,
                  typename t_zeta_star,
                  typename t_gamma,
                  typename t_gamma_star,
                  typename t_tsurface,
                  typename t_uout,
                  typename t_normals>
        void multisurface_steady_wake
        (
            const t_zeta&       zeta,
            const t_zeta_star&  zeta_star,
            const t_gamma&      gamma,
            const t_gamma_star& gamma_star,
            const t_tsurface&   target_surface,
            const bool&         horseshoe,
            t_uout&             uout,
            const bool&         image_method = false,
            const t_normals&    normal = NULL,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );

        template <typename t_zeta,
                  typename t_zeta_star,
                  typename t_gamma,
                  typename t_gamma_star,
                  typename t_tsurface,
                  typename t_uout,
                  typename t_normals>
        void multisurface_unsteady_wake
        (
            const t_zeta&       zeta,
            const t_zeta_star&  zeta_star,
            const t_gamma&      gamma,
            const t_gamma_star& gamma_star,
            const t_tsurface&   target_surface,
            t_uout&             uout,
            const bool&         image_method,
            const t_normals&    normal,
            const int&          n_rows = -1
        );

        template <typename t_zeta,
                  typename t_gamma,
                  typename t_ttriad,
                  typename t_uout>
        void surface
        (
            const t_zeta&       zeta,
            const t_gamma&      gamma,
            const t_ttriad&     target_triad,
            t_uout&             uout,
            unsigned int        Mstart = 0,
            unsigned int        Nstart = 0,
            unsigned int        Mend   = -1,
            unsigned int        Nend   = -1,
            const bool&         image_method = false,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );

        template <typename t_zeta,
                  typename t_zeta_star,
                  typename t_gamma,
                  typename t_gamma_star,
                  typename t_ttriad,
                  typename t_uout>
        void surface_with_steady_wake
        (
            const t_zeta&       zeta,
            const t_zeta_star&  zeta_star,
            const t_gamma&      gamma,
            const t_gamma_star& gamma_star,
            const t_ttriad&     target_triad,
            const bool&         horseshoe,
            t_uout&             uout,
            const bool&         image_method = false,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );

        template <typename t_zeta,
                  typename t_zeta_star,
                  typename t_gamma,
                  typename t_gamma_star,
                  typename t_ttriad,
                  typename t_uout>
        void surface_with_unsteady_wake
        (
            const t_zeta&       zeta,
            const t_zeta_star&  zeta_star,
            const t_gamma&      gamma,
            const t_gamma_star& gamma_star,
            const t_ttriad&     target_triad,
            t_uout&             uout,
            const bool&         image_method,
            const int&          n_rows = -1 // default val = -1
        );

        template <typename t_triad,
                  typename t_block>
                  //typename t_uind>
        UVLM::Types::Vector3 vortex_ring
        (
            const t_triad& target_triad,
            const t_block& x,
            const t_block& y,
            const t_block& z,
            const UVLM::Types::Real& gamma_star,
            // t_uind& uind,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );

        template <typename t_triad,
                  typename t_block>
        void horseshoe
        (
            const t_triad& target_triad,
            const t_block& x,
            const t_block& y,
            const t_block& z,
            const UVLM::Types::Real& gamma,
            UVLM::Types::Vector3& uind,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );

        template <typename t_triad>
                  //typename t_uind>
        UVLM::Types::Vector3 segment
        (
            const t_triad& target_triad,
            const UVLM::Types::Vector3& v1,
            const UVLM::Types::Vector3& v2,
            const UVLM::Types::Real& gamma,
            // t_uind& uind,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );



        template <typename t_zeta,
                  typename t_zeta_star,
                  typename t_gamma,
                  typename t_gamma_star,
                  typename t_uout>
        void total_induced_velocity_on_wake
        (
            const t_zeta&       zeta,
            const t_zeta_star&  zeta_star,
            const t_gamma&      gamma,
            const t_gamma_star& gamma_star,
            t_uout&             uout,
            const bool&         image_method = false,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );



        template <typename t_zeta,
                  typename t_gamma,
                  typename t_zeta_col,
                  typename t_u_ind>
        void whole_surface_on_surface
        (
            const t_zeta& zeta,
            const t_gamma& gamma,
            const t_zeta_col& zeta_col,
            t_u_ind& u_ind,
            const bool image_method = false
        );


        template <typename t_zeta,
                  typename t_gamma,
                  typename t_ttriad>
                  // typename t_uout>
        UVLM::Types::Vector3 whole_surface
        (
            const t_zeta&       zeta,
            const t_gamma&      gamma,
            const t_ttriad&     target_triad,
            // t_uout&             uout,
            unsigned int        Mstart = 0,
            unsigned int        Nstart = 0,
            unsigned int        Mend = -1,
            unsigned int        Nend = -1,
            const bool&         image_method = false,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );

        template <typename t_ttriad,
                  typename t_zeta,
                  typename t_zeta_star,
                  typename t_gamma,
                  typename t_gamma_star,
                  typename t_uout>
        void total_induced_velocity_on_point
        (
            const t_ttriad&     target_triad,
            const t_zeta&       zeta,
            const t_zeta_star&  zeta_star,
            const t_gamma&      gamma,
            const t_gamma_star& gamma_star,
            t_uout&             uout,
            const bool&         image_method,
            const UVLM::Types::Real vortex_radius = VORTEX_RADIUS
        );
    }
}



namespace UVLMlin{

  void biot_panel_map( map_RowVec3& velP,
             const map_RowVec3 zetaP,
             const map_Mat4by3 ZetaPanel,
             const double gamma );


  void der_biot_panel(Matrix3d& DerP,
          Matrix3d DerVertices[Nvert],
          const RowVector3d zetaP,
          const Matrix4by3d ZetaPanel,
          const double gamma );


  void der_biot_panel_map( map_Mat3by3& DerP,
             Vec_map_Mat3by3& DerVertices,
             const map_RowVec3 zetaP,
             const map_Mat4by3 ZetaPanel,
             const double gamma );


  void der_runit( Matrix3d& Der,
          const RowVector3d& rv,
          double rinv,
          double minus_rinv3);


  Matrix3d Dvcross_by_skew3d(const Matrix3d& Dvcross,
                 const RowVector3d& rv);


  void dvinddzeta(map_Mat3by3 DerC,
          map_Mat DerV,
          const map_RowVec3 zetaC,
          Vec_map_Mat ZetaIn,
          map_Mat GammaIn,
          int& M_in,
          int& N_in,
          int& Kzeta_in,
          bool& IsBound,
          int& M_in_bound, // M of bound surf associated
          int& Kzeta_in_bound
          );


  void aic3(  map_Mat AIC3,
        const map_RowVec3 zetaC,
        Vec_map_Mat ZetaIn,
        int& M_in,
        int& N_in);

  void ind_vel(map_RowVec3 velC,
        const map_RowVec3 zetaC,
        Vec_map_Mat ZetaIn,
        map_Mat GammaIn,
        int& M_in,
        int& N_in);

}



// SOURCE CODE
template <typename t_triad>
          // typename t_uind>
UVLM::Types::Vector3 UVLM::BiotSavart::segment
        (
            const t_triad& rp,
            const UVLM::Types::Vector3& v1,
            const UVLM::Types::Vector3& v2,
            const UVLM::Types::Real& gamma,
            //t_uind& uind,
            const UVLM::Types::Real vortex_radius
        )
{
    UVLM::Types::Vector3 uind;
    uind.setZero();
    UVLM::Types::Vector3 r0 = v2 - v1;
    UVLM::Types::Vector3 r1 = rp - v1;
    UVLM::Types::Vector3 r2 = rp - v2;
    UVLM::Types::Real r0_mod = r0.norm();
    UVLM::Types::Real r1_mod = r1.norm();
    UVLM::Types::Real r2_mod = r2.norm();

    UVLM::Types::Real relative_vortex_radius = r0_mod*vortex_radius;

    UVLM::Types::Real s_v = 0.5*(r1_mod + r2_mod + r0_mod);
    UVLM::Types::Real a_v;

    a_v = 2.0/(EPSILON_VORTEX + r0_mod);
    a_v *= sqrt(s_v*(s_v - r1_mod)*
                    (s_v - r2_mod)*
                    (s_v - r0_mod));

    if (std::isnan(a_v) || (a_v < relative_vortex_radius))
    {
        return uind;
    }

    UVLM::Types::Vector3 r1_cross_r2 = r1.cross(r2);
    UVLM::Types::Real r0_dot_r1 = r0.dot(r1);
    UVLM::Types::Real r0_dot_r2 = r0.dot(r2);
    UVLM::Types::Real r1_cross_r2_mod_sq = r1_cross_r2.squaredNorm();

    UVLM::Types::Real K;
    K = (gamma/(UVLM::Constants::PI4*r1_cross_r2_mod_sq + EPSILON_VORTEX))*
        (r0_dot_r1/(r1_mod + EPSILON_VORTEX) - r0_dot_r2/(r2_mod + EPSILON_VORTEX));

    uind = K*r1_cross_r2;
    return uind;
}


template <typename t_triad,
          typename t_block>
void UVLM::BiotSavart::horseshoe
(
    const t_triad& target_triad,
    const t_block& x,
    const t_block& y,
    const t_block& z,
    const UVLM::Types::Real& gamma_star,
    UVLM::Types::Vector3& uind,
    const UVLM::Types::Real vortex_radius
)
{
    // three segments.
    //
    //     0___________3
    //      |         |
    //      |         |
    //      |         |
    //      |         |
    //      |         |
    //      |         |
    //      |         |
    //     1|         |2
    //
    // segments 0-1 and 2-3 are represented as length 1, but they are effectively
    // infinite
    // segment 3-0 is considered as a normal one

    UVLM::Types::Vector3 v1;
    UVLM::Types::Vector3 v2;
    // segment 3-0
    v1 << x(UVLM::Mapping::vortex_indices(3, 0),
            UVLM::Mapping::vortex_indices(3, 1)),
          y(UVLM::Mapping::vortex_indices(3, 0),
            UVLM::Mapping::vortex_indices(3, 1)),
          z(UVLM::Mapping::vortex_indices(3, 0),
            UVLM::Mapping::vortex_indices(3, 1));
    v2 << x(UVLM::Mapping::vortex_indices(0, 0),
            UVLM::Mapping::vortex_indices(0, 1)),
          y(UVLM::Mapping::vortex_indices(0, 0),
            UVLM::Mapping::vortex_indices(0, 1)),
          z(UVLM::Mapping::vortex_indices(0, 0),
            UVLM::Mapping::vortex_indices(0, 1));
    uind += UVLM::BiotSavart::segment(target_triad,
                              v1,
                              v2,
                              gamma_star);
                              // uind);

    // segment 0-1
    v1 << x(UVLM::Mapping::vortex_indices(0, 0),
            UVLM::Mapping::vortex_indices(0, 1)),
          y(UVLM::Mapping::vortex_indices(0, 0),
            UVLM::Mapping::vortex_indices(0, 1)),
          z(UVLM::Mapping::vortex_indices(0, 0),
            UVLM::Mapping::vortex_indices(0, 1));
    v2 << x(UVLM::Mapping::vortex_indices(1, 0),
            UVLM::Mapping::vortex_indices(1, 1)),
          y(UVLM::Mapping::vortex_indices(1, 0),
            UVLM::Mapping::vortex_indices(1, 1)),
          z(UVLM::Mapping::vortex_indices(1, 0),
            UVLM::Mapping::vortex_indices(1, 1));

    // here the segment will be considered as 1----->2 and the
    // point 2 is in infinity, so beta2=pi
    UVLM::Types::Vector3 r0 = v2 - v1;
    UVLM::Types::Vector3 r1 = target_triad - v1;
    UVLM::Types::Vector3 r2 = target_triad - v2;
    UVLM::Types::Vector3 r1_cross_r2 = r1.cross(r2);
    UVLM::Types::Real dist = (r1_cross_r2).norm()/r0.norm();
    UVLM::Types::Real beta1;
    UVLM::Types::Real beta2;
    UVLM::Types::Vector3 u_radial;
    if (!((r1.norm() < vortex_radius) ||
         (r2.norm() < vortex_radius) ||
         (r1_cross_r2.norm() < vortex_radius)))
    {
        beta1 = r0.dot(r1)/(r0.norm()*r1.norm());
        beta2 = UVLM::Constants::PI;

        u_radial = (r1_cross_r2)/(r1_cross_r2).norm();

        uind += gamma_star/(UVLM::Constants::PI4*dist)*(beta1 + 1.0)*
                u_radial;
    }

    // segment 2-3
    v1 << x(UVLM::Mapping::vortex_indices(2, 0),
            UVLM::Mapping::vortex_indices(2, 1)),
          y(UVLM::Mapping::vortex_indices(2, 0),
            UVLM::Mapping::vortex_indices(2, 1)),
          z(UVLM::Mapping::vortex_indices(2, 0),
            UVLM::Mapping::vortex_indices(2, 1));
    v2 << x(UVLM::Mapping::vortex_indices(3, 0),
            UVLM::Mapping::vortex_indices(3, 1)),
          y(UVLM::Mapping::vortex_indices(3, 0),
            UVLM::Mapping::vortex_indices(3, 1)),
          z(UVLM::Mapping::vortex_indices(3, 0),
            UVLM::Mapping::vortex_indices(3, 1));

    // here the segment will be considered as 1----->2 and the
    // point 1 is in infinity, so beta1=0
    r0 = v2 - v1;
    r1 = target_triad - v1;
    r2 = target_triad - v2;
    r1_cross_r2 = r1.cross(r2);
    dist = (r1_cross_r2).norm()/r0.norm();
    if (!((r1.norm() < vortex_radius) ||
         (r2.norm() < vortex_radius) ||
         (r1_cross_r2.norm() < vortex_radius)))
    {
        beta2 = r0.dot(r2)/(r0.norm()*r2.norm());
        dist = (r1.cross(r2)).norm()/r0.norm();

        u_radial = (r1_cross_r2)/(r1_cross_r2).norm();

        uind += gamma_star/(UVLM::Constants::PI4*dist)*(1.0 - beta2)*
                u_radial;
    }
}


template <typename t_triad,
          typename t_block>
          // typename t_uind>
UVLM::Types::Vector3 UVLM::BiotSavart::vortex_ring
(
    const t_triad& target_triad,
    const t_block& x,
    const t_block& y,
    const t_block& z,
    const UVLM::Types::Real& gamma,
    // t_uind& uind,
    const UVLM::Types::Real vortex_radius
)
{
    UVLM::Types::Vector3 uind;
    uind.setZero();
    if (std::abs(gamma) < UVLM::Constants::EPSILON)
    {
        return uind;
    }

    UVLM::Types::Vector3 v1;
    UVLM::Types::Vector3 v2;
    const unsigned int n_segment = 4;
    for (unsigned int i_segment=0; i_segment<n_segment; ++i_segment)
    {
        unsigned int start = i_segment;
        unsigned int end = (start + 1)%n_segment;

        v1 << x(UVLM::Mapping::vortex_indices(start, 0),
                UVLM::Mapping::vortex_indices(start, 1)),
              y(UVLM::Mapping::vortex_indices(start, 0),
                UVLM::Mapping::vortex_indices(start, 1)),
              z(UVLM::Mapping::vortex_indices(start, 0),
                UVLM::Mapping::vortex_indices(start, 1));
        v2 << x(UVLM::Mapping::vortex_indices(end, 0),
                UVLM::Mapping::vortex_indices(end, 1)),
              y(UVLM::Mapping::vortex_indices(end, 0),
                UVLM::Mapping::vortex_indices(end, 1)),
              z(UVLM::Mapping::vortex_indices(end, 0),
                UVLM::Mapping::vortex_indices(end, 1));

        uind += UVLM::BiotSavart::segment(target_triad,
                                          v1,
                                          v2,
                                          gamma);
                                          // uind);
    }
    return uind;
}


template <typename t_zeta,
          typename t_gamma,
          typename t_ttriad,
          typename t_uout>
void UVLM::BiotSavart::surface
(
    const t_zeta&       zeta,
    const t_gamma&      gamma,
    const t_ttriad&     target_triad,
    t_uout&             uout,
    unsigned int        Mstart,
    unsigned int        Nstart,
    unsigned int        Mend,
    unsigned int        Nend,
    const bool&         image_method,
    const UVLM::Types::Real vortex_radius
)
{
    // If Mend or Nend are == -1, their values are taken as the surface M and N
    if (Mend == -1) {Mend = gamma.rows();}
    if (Nend == -1) {Nend = gamma.cols();}

    // #pragma omp parallel for collapse(2)
    UVLM::Types::Vector3 temp_uout;
    for (unsigned int i=Mstart; i<Mend; ++i)
    {
        for (unsigned int j=Nstart; j<Nend; ++j)
        {
            temp_uout = UVLM::BiotSavart::vortex_ring(target_triad,
                                          zeta[0].template block<2, 2>(i,j),
                                          zeta[1].template block<2, 2>(i,j),
                                          zeta[2].template block<2, 2>(i,j),
                                          gamma(i,j));
                                          // temp_uout);
            uout[0](i, j) += temp_uout(0);
            uout[1](i, j) += temp_uout(1);
            uout[2](i, j) += temp_uout(2);
        }
    }
}


template <typename t_zeta,
          typename t_zeta_star,
          typename t_gamma,
          typename t_gamma_star,
          typename t_ttriad,
          typename t_uout>
void UVLM::BiotSavart::surface_with_steady_wake
(
    const t_zeta&       zeta,
    const t_zeta_star&  zeta_star,
    const t_gamma&      gamma,
    const t_gamma_star& gamma_star,
    const t_ttriad&     target_triad,
    const bool&         horseshoe,
    t_uout&             uout,
    const bool&         image_method,
    const UVLM::Types::Real vortex_radius
)
{
    const uint Mstart = 0;
    const uint Nstart = 0;
    const uint Mend = gamma.rows();
    const uint Nend = gamma.cols();

    UVLM::BiotSavart::surface(zeta,
                              gamma,
                              target_triad,
                              uout,
                              Mstart,
                              Nstart,
                              Mend,
                              Nend,
                              image_method);

    const uint i0 = 0;
    const uint i = Mend - 1;
    if (horseshoe)
    {
        UVLM::Types::Vector3 temp_uout;
        for (unsigned int j=Nstart; j<Nend; ++j)
        {
            temp_uout.setZero();
            UVLM::BiotSavart::horseshoe(target_triad,
                                        zeta_star[0].template block<2,2>(i0,j),
                                        zeta_star[1].template block<2,2>(i0,j),
                                        zeta_star[2].template block<2,2>(i0,j),
                                        gamma_star(i0,j),
                                        temp_uout);
            uout[0](i, j) += temp_uout(0);
            uout[1](i, j) += temp_uout(1);
            uout[2](i, j) += temp_uout(2);
        }
    } else
    {
        const uint mstar = gamma_star.rows();
        UVLM::Types::Vector3 temp_uout;
        for (unsigned int j=Nstart; j<Nend; ++j)
        {
            temp_uout.setZero();
            // #pragma omp parallel for collapse(1) reduction(sum_Vector3: temp_uout)
            for (uint i_star=0; i_star<mstar; ++i_star)
            {
                temp_uout += UVLM::BiotSavart::vortex_ring(target_triad,
                                              zeta_star[0].template block<2,2>(i_star, j),
                                              zeta_star[1].template block<2,2>(i_star, j),
                                              zeta_star[2].template block<2,2>(i_star, j),
                                              gamma_star(i_star, j));
                                              // temp_uout);
            }
            uout[0](i, j) += temp_uout(0);
            uout[1](i, j) += temp_uout(1);
            uout[2](i, j) += temp_uout(2);
        }
    }
}


template <typename t_zeta,
          typename t_zeta_star,
          typename t_gamma,
          typename t_gamma_star,
          typename t_ttriad,
          typename t_uout>
void UVLM::BiotSavart::surface_with_unsteady_wake
(
    const t_zeta&       zeta,
    const t_zeta_star&  zeta_star,
    const t_gamma&      gamma,
    const t_gamma_star& gamma_star,
    const t_ttriad&     target_triad,
    t_uout&             uout,
    const bool&         image_method,
    const int&          n_rows // default val = -1
)
{
    const uint Mstart = 0;
    const uint Nstart = 0;
    const uint Mend = gamma.rows();
    const uint Nend = gamma.cols();

    // UVLM::Types::Vector3 temp_uout;
    const uint ii = 0;
    // Surface contribution
    UVLM::BiotSavart::surface(zeta,
                              gamma,
                              target_triad,
                              uout,
                              Mstart,
                              Nstart,
                              Mend,
                              Nend,
                              image_method);

    // wake contribution
    // n_rows controls the number of panels that are included
    // in the final result. Usually for unsteady wake, the value
    // will be 1 when computing AIC coeffs.
    // unless if gamma_star is a dummy one, just a row with ones.
    const uint mstar = (n_rows == -1) ? gamma_star.rows():n_rows;
    const uint i = Mend - 1;
    UVLM::Types::Vector3 temp_uout;
    for (uint j=Nstart; j<Nend; ++j)
    {
        temp_uout.setZero();
        // #pragma omp parallel for collapse(1) reduction(sum_Vector3: temp_uout)
        for (uint i_star=0; i_star<mstar; ++i_star)
        {
            // std::cout << "WARNING: this should not be computed" << std::endl;
            temp_uout += UVLM::BiotSavart::vortex_ring(target_triad,
                                          zeta_star[0].template block<2,2>(i_star, j),
                                          zeta_star[1].template block<2,2>(i_star, j),
                                          zeta_star[2].template block<2,2>(i_star, j),
                                          gamma_star(i_star, j));
                                          // temp_uout);
        }
        uout[0](i, j) += temp_uout(0);
        uout[1](i, j) += temp_uout(1);
        uout[2](i, j) += temp_uout(2);
    }
}

template <typename t_zeta,
          typename t_gamma,
          typename t_tsurface,
          typename t_uout,
          typename t_normals>
void UVLM::BiotSavart::multisurface
(
    const t_zeta&       zeta,
    const t_gamma&      gamma,
    const t_tsurface&   target_surface,
    t_uout&             uout,
    const bool&         image_method,
    const t_normals&    normal,
    const UVLM::Types::Real vortex_radius
)
{
    const unsigned int rows_collocation = target_surface[0].rows();
    const unsigned int cols_collocation = target_surface[0].cols();

    UVLM::Types::VecMatrixX temp_uout;
    UVLM::Types::allocate_VecMat(temp_uout, zeta, -1);
    UVLM::Types::Vector3 target_triad;

    int collocation_counter = -1;
    // int surface_counter;
    unsigned int surf_rows = gamma.rows();
    unsigned int surf_cols = gamma.cols();

    for (unsigned int i_col=0; i_col<rows_collocation; ++i_col)
    {
        for (unsigned int j_col=0; j_col<cols_collocation; ++j_col)
        {
            ++collocation_counter;
            UVLM::Types::initialise_VecMat(temp_uout, 0.0);
            target_triad << target_surface[0](i_col, j_col),
                            target_surface[1](i_col, j_col),
                            target_surface[2](i_col, j_col);
            UVLM::BiotSavart::surface(zeta,
                                      gamma,
                                      target_triad,
                                      temp_uout);

            // surface_counter = -1;
            // #pragma omp parallel for collapse(2)
            for (unsigned int i_surf=0; i_surf<surf_rows; ++i_surf)
            {
                for (unsigned int j_surf=0; j_surf<surf_cols; ++j_surf)
                {
                    int surface_counter = j_surf + i_surf*surf_cols;
                    uout(collocation_counter, surface_counter) +=
                        temp_uout[0](i_surf, j_surf)*normal[0](i_col, j_col) +
                        temp_uout[1](i_surf, j_surf)*normal[1](i_col, j_col) +
                        temp_uout[2](i_surf, j_surf)*normal[2](i_col, j_col);
                }
            }
        }
    }
}





template <typename t_zeta,
          typename t_zeta_star,
          typename t_gamma,
          typename t_gamma_star,
          typename t_tsurface,
          typename t_uout,
          typename t_normals>
void UVLM::BiotSavart::multisurface_steady_wake
(
    const t_zeta&       zeta,
    const t_zeta_star&  zeta_star,
    const t_gamma&      gamma,
    const t_gamma_star& gamma_star,
    const t_tsurface&   target_surface,
    const bool&         horseshoe,
    t_uout&             uout,
    const bool&         image_method,
    const t_normals&    normal,
    const UVLM::Types::Real vortex_radius
)
{
    const unsigned int rows_collocation = target_surface[0].rows();
    const unsigned int cols_collocation = target_surface[0].cols();

    UVLM::Types::VecMatrixX temp_uout;
    UVLM::Types::allocate_VecMat(temp_uout, zeta, -1);
    UVLM::Types::Vector3 target_triad;

    int collocation_counter = -1;
    // int surface_counter;
    const uint surf_rows = gamma.rows();
    const uint surf_cols = gamma.cols();

    for (unsigned int i_col=0; i_col<rows_collocation; ++i_col)
    {
        for (unsigned int j_col=0; j_col<cols_collocation; ++j_col)
        {
            // collocation_counter = i_col*cols_collocation + j_col;
            ++collocation_counter;
            target_triad << target_surface[0](i_col, j_col),
                            target_surface[1](i_col, j_col),
                            target_surface[2](i_col, j_col);
            UVLM::Types::initialise_VecMat(temp_uout, 0.0);

            UVLM::BiotSavart::surface_with_steady_wake(zeta,
                                                       zeta_star,
                                                       gamma,
                                                       gamma_star,
                                                       target_triad,
                                                       horseshoe,
                                                       temp_uout
                                                      );

            // #pragma omp parallel for collapse(2)
            for (unsigned int i_surf=0; i_surf<surf_rows; ++i_surf)
            {
                for (unsigned int j_surf=0; j_surf<surf_cols; ++j_surf)
                {
                    int surface_counter = i_surf*surf_cols + j_surf;
                    uout(collocation_counter, surface_counter) +=
                        temp_uout[0](i_surf, j_surf)*normal[0](i_col, j_col) +
                        temp_uout[1](i_surf, j_surf)*normal[1](i_col, j_col) +
                        temp_uout[2](i_surf, j_surf)*normal[2](i_col, j_col);
                }
            }
        }
    }
}

template <typename t_zeta,
          typename t_zeta_star,
          typename t_gamma,
          typename t_gamma_star,
          typename t_tsurface,
          typename t_uout,
          typename t_normals>
void UVLM::BiotSavart::multisurface_unsteady_wake
(
    const t_zeta&       zeta,
    const t_zeta_star&  zeta_star,
    const t_gamma&      gamma,
    const t_gamma_star& gamma_star,
    const t_tsurface&   target_surface,
    t_uout&             uout,
    const bool&         image_method,
    const t_normals&    normal,
    const int&          n_rows // default val = -1
)
{
    const unsigned int rows_collocation = target_surface[0].rows();
    const unsigned int cols_collocation = target_surface[0].cols();

    UVLM::Types::VecMatrixX temp_uout;
    UVLM::Types::allocate_VecMat(temp_uout, zeta, -1);
    UVLM::Types::Vector3 target_triad;

    int collocation_counter = -1;
    // int surface_counter;
    unsigned int surf_rows = gamma.rows();
    unsigned int surf_cols = gamma.cols();

    for (unsigned int i_col=0; i_col<rows_collocation; ++i_col)
    {
        for (unsigned int j_col=0; j_col<cols_collocation; ++j_col)
        {
            ++collocation_counter;
            target_triad << target_surface[0](i_col, j_col),
                            target_surface[1](i_col, j_col),
                            target_surface[2](i_col, j_col);
            UVLM::Types::initialise_VecMat(temp_uout, 0.0);

            UVLM::BiotSavart::surface_with_unsteady_wake(zeta,
                                                         zeta_star,
                                                         gamma,
                                                         gamma_star,
                                                         target_triad,
                                                         temp_uout,
                                                         image_method,
                                                         n_rows
                                                        );

            // #pragma omp parallel for collapse(2)
            for (unsigned int i_surf=0; i_surf<surf_rows; ++i_surf)
            {
                for (unsigned int j_surf=0; j_surf<surf_cols; ++j_surf)
                {
                    int surface_counter = i_surf*surf_cols + j_surf;
                    uout(collocation_counter, surface_counter) +=
                        temp_uout[0](i_surf, j_surf)*normal[0](i_col, j_col) +
                        temp_uout[1](i_surf, j_surf)*normal[1](i_col, j_col) +
                        temp_uout[2](i_surf, j_surf)*normal[2](i_col, j_col);
                }
            }
        }
    }
}

// template <typename t_zeta,
//           typename t_gamma,
//           typename t_zeta_col,
//           typename t_u_ind>
// void UVLM::BiotSavart::multisurface_on_multisurface
// (
//     const t_zeta& zeta,
//     const t_gamma& gamma,
//     const t_zeta_col& zeta_col,
//     const bool image_method,
//     t_u_ind& u_ind
// )
// {
//
// }

template <typename t_zeta,
          typename t_gamma,
          typename t_zeta_col,
          typename t_u_ind>
void UVLM::BiotSavart::whole_surface_on_surface
(
    const t_zeta& zeta,
    const t_gamma& gamma,
    const t_zeta_col& zeta_col,
    t_u_ind& u_ind,
    const bool image_method
)
{
    const uint col_n_M = zeta_col[0].rows();
    const uint col_n_N = zeta_col[0].cols();
    const uint n_M = zeta[0].rows();
    const uint n_N = zeta[0].cols();

    // #pragma omp parallel for collapse(2) reduction(sum_Vector3: uout)
    for (uint col_i_M=0; col_i_M<col_n_M; ++col_i_M)
    {
        for (uint col_j_N=0; col_j_N<col_n_N; ++col_j_N)
        {
            UVLM::Types::Vector3 target_triad;
            UVLM::Types::Vector3 uout;

            target_triad << zeta_col[0](col_i_M, col_j_N),
                            zeta_col[1](col_i_M, col_j_N),
                            zeta_col[2](col_i_M, col_j_N);
            uout = UVLM::BiotSavart::whole_surface
                    (
                        zeta,
                        gamma,
                        target_triad,
                        // uout,
                        image_method
                    );
            u_ind[0](col_i_M, col_j_N) += uout(0);
            u_ind[1](col_i_M, col_j_N) += uout(1);
            u_ind[2](col_i_M, col_j_N) += uout(2);
        }
    }
}


template <typename t_zeta,
          typename t_gamma,
          typename t_ttriad>
          // typename t_uout>
UVLM::Types::Vector3 UVLM::BiotSavart::whole_surface
(
    const t_zeta&       zeta,
    const t_gamma&      gamma,
    const t_ttriad&     target_triad,
    // t_uout&             uout,
    unsigned int        Mstart,
    unsigned int        Nstart,
    unsigned int        Mend,
    unsigned int        Nend,
    const bool&         image_method,
    const UVLM::Types::Real vortex_radius
)
{
    // If Mend or Nend are == -1, their values are taken as the surface M and N
    if (Mend == -1) {Mend = gamma.rows();}
    if (Nend == -1) {Nend = gamma.cols();}

    UVLM::Types::Vector3 uout;
    uout.setZero();
    UVLM::Types::Vector3 temp_uout;
    UVLM::Types::Vector3 v1;
    UVLM::Types::Vector3 v2;
    UVLM::Types::Real delta_gamma;
    for (unsigned int i=Mstart; i<Mend; ++i)
    {

        for (unsigned int j=Nstart; j<Nend; ++j)
        {

            // Spanwise vortices
            v1 << zeta[0](i, j),
                  zeta[1](i, j),
                  zeta[2](i, j);
            v2 << zeta[0](i, j+1),
                  zeta[1](i, j+1),
                  zeta[2](i, j+1);

            if (i == Mstart){
                delta_gamma = gamma(i, j);
            } else {
                delta_gamma = gamma(i, j) - gamma(i-1, j);
            }
            temp_uout = UVLM::BiotSavart::segment(target_triad,
                                                  v1,
                                                  v2,
                                                  -delta_gamma);

            // Streamwise/chordwise vortices
            v2 << zeta[0](i+1, j),
                  zeta[1](i+1, j),
                  zeta[2](i+1, j);

            if (j == Nstart){
                delta_gamma = -gamma(i, j);
            } else {
                delta_gamma = gamma(i, j-1) - gamma(i, j);
            }
            temp_uout += UVLM::BiotSavart::segment(target_triad,
                                                  v1,
                                                  v2,
                                                  -delta_gamma);

            uout += temp_uout;
        }
    }
    for (unsigned int j=Nstart; j<Nend; ++j)
    {
        // Spanwise vortices
        v1 << zeta[0](Mend, j),
              zeta[1](Mend, j),
              zeta[2](Mend, j);
        v2 << zeta[0](Mend, j+1),
              zeta[1](Mend, j+1),
              zeta[2](Mend, j+1);
        uout += UVLM::BiotSavart::segment(target_triad,
                                              v1,
                                              v2,
                                              gamma(Mend-1,j));
    }

    for (unsigned int i=Mstart; i<Mend; ++i)
    {
        // Streamwise/chordwise vortices
        v1 << zeta[0](i, Nend),
              zeta[1](i, Nend),
              zeta[2](i, Nend);
        v2 << zeta[0](i+1, Nend),
              zeta[1](i+1, Nend),
              zeta[2](i+1, Nend);

        uout += UVLM::BiotSavart::segment(target_triad,
                                              v1,
                                              v2,
                                              -gamma(i, Nend-1));
    }
    return uout;
}

template <typename t_zeta,
          typename t_zeta_star,
          typename t_gamma,
          typename t_gamma_star,
          typename t_uout>
void UVLM::BiotSavart::total_induced_velocity_on_wake
(
    const t_zeta&       zeta,
    const t_zeta_star&  zeta_star,
    const t_gamma&      gamma,
    const t_gamma_star& gamma_star,
    t_uout&             uout,
    const bool&         image_method,
    const UVLM::Types::Real vortex_radius
)
{
    const uint n_surf = zeta.size();
    for (uint col_i_surf=0; col_i_surf<n_surf; ++col_i_surf)
    {
        for (uint i_surf=0; i_surf<n_surf; ++i_surf)
        {
            // wake on wake
            UVLM::BiotSavart::whole_surface_on_surface
            (
                zeta_star[i_surf],
                gamma_star[i_surf],
                zeta_star[col_i_surf],
                uout[col_i_surf],
                image_method
            );
            // surface on wake
            UVLM::BiotSavart::whole_surface_on_surface
            (
                zeta[i_surf],
                gamma[i_surf],
                zeta_star[col_i_surf],
                uout[col_i_surf],
                image_method
            );
        }
    }
}

template <typename t_ttriad,
          typename t_zeta,
          typename t_zeta_star,
          typename t_gamma,
          typename t_gamma_star,
          typename t_uout>
void UVLM::BiotSavart::total_induced_velocity_on_point
(
    const t_ttriad&     target_triad,
    const t_zeta&       zeta,
    const t_zeta_star&  zeta_star,
    const t_gamma&      gamma,
    const t_gamma_star& gamma_star,
    t_uout&             uout,
    const bool&         image_method,
    const UVLM::Types::Real vortex_radius
)
{
    uout.setZero();
    const uint n_surf = zeta.size();
    for (uint i_surf=0; i_surf<n_surf; ++i_surf)
    {
        // wake on point
        uout += UVLM::BiotSavart::whole_surface
        (
            zeta_star[i_surf],
            gamma_star[i_surf],
            target_triad,
            // sum_uout,
            0,
            0,
            -1,
            -1,
            image_method,
            vortex_radius
        );
        // surface on point
        uout += UVLM::BiotSavart::whole_surface
        (
            zeta[i_surf],
            gamma[i_surf],
            target_triad,
            // sum_uout,
            0,
            0,
            -1,
            -1,
            image_method,
            vortex_radius
        );
    }
}




namespace UVLMlin{

  const double PI = 3.1415926535897932384626433832795028841971;
  const double PIquart=0.25/PI;
  const int svec[Nvert]={0, 1, 2, 3}; // seg. no.
  const int avec[Nvert]={0, 1, 2, 3}; // seg. no.
  const int bvec[Nvert]={1, 2, 3, 0}; // seg. no.
  const int dm[Nvert]={0,1,1,0};
  const int dn[Nvert]={0,0,1,1};

  void biot_panel_map( map_RowVec3& velP,
             const map_RowVec3 zetaP,
             const map_Mat4by3 ZetaPanel,
             const double gamma ){
    /*
    This implementation works with mapping objects.
    */


    // declarations
    int ii,aa,bb;
    const double Cbiot=PIquart*gamma;
    double vcr2;

    RowVector3d RAB, Vcr;
    Vector3d Vsc;
    Vector4d RABsq;

    Matrix4by3d R;    // vectors P - vertex matrix
    Matrix4by3d Runit;  // unit vectors P - vertex matrix


    // ----------------------------------------------- Compute common variables
    // these are constants or variables depending only on vertices and P coords
    for(ii=0;ii<Nvert;ii++){
      R.row(ii)=zetaP-ZetaPanel.row(ii);
      Runit.row(ii)=R.row(ii)/R.row(ii).norm();
    }


    // -------------------------------------------------- Loop through segments
    for(ii=0;ii<Nvert;ii++){

      aa=avec[ii];
      bb=bvec[ii];

      RAB=ZetaPanel.row(bb)-ZetaPanel.row(aa);  // segment vector
      Vcr=R.row(aa).cross(R.row(bb));
      vcr2=Vcr.dot(Vcr);
      if (vcr2<VORTEX_RADIUS_SQ*RAB.dot(RAB)) continue;

      velP += ((Cbiot/vcr2) * RAB.dot(Runit.row(aa)-Runit.row(bb))) *Vcr;
    }
  }



  // -----------------------------------------------------------------------------


  void der_biot_panel( Matrix3d& DerP, Matrix3d DerVertices[Nvert],
    const RowVector3d zetaP, const Matrix4by3d ZetaPanel, const double gamma ){
    /* This implementation is no suitable for python interface */


    // declarations
    int ii,aa,bb;
    const double Cbiot=PIquart*gamma;
    double r1inv, vcr2, vcr2inv, vcr4inv, dotprod, diag_fact, off_fact;

    RowVector3d RAB, Vcr, Tv;
    Vector3d Vsc;

    Matrix3d Dvcross, Ddiff, dQ_dRA, dQ_dRB, dQ_dRAB;

    Matrix4by3d R;    // vectors P - vertex matrix
    Matrix4by3d Runit;  // unit vectors P - vertex matrix

    Matrix3d Array_Der_runit[Nvert]; // as a static arrays (we know size)


    // ----------------------------------------------- Compute common variables
    // these are constants or variables depending only on vertices and P coords
    for(ii=0;ii<Nvert;ii++){

      R.row(ii)=zetaP-ZetaPanel.row(ii);

      r1inv=1./R.row(ii).norm();
      Runit.row(ii)=R.row(ii)*r1inv;

      der_runit( Array_Der_runit[ii], R.row(ii), r1inv, -std::pow(r1inv,3) );
    }


    // -------------------------------------------------- Loop through segments
    for(ii=0;ii<Nvert;ii++){

      // vertices indices
      aa=avec[ii];
      bb=bvec[ii];

      // utility vars
      RAB=ZetaPanel.row(bb)-ZetaPanel.row(aa);  // segment vector
      Vcr=R.row(aa).cross(R.row(bb));
      vcr2=Vcr.dot(Vcr);
      if (vcr2<VORTEX_RADIUS_SQ*RAB.dot(RAB)){
        //cout << endl << "Skipping seg. " << ii << endl;
        continue;}
      Tv=Runit.row(aa)-Runit.row(bb);
      dotprod=RAB.dot(Tv);


      // ------------------------------------------ cross-product derivatives
      // lower triangular part only
      vcr2inv=1./vcr2;
      vcr4inv=vcr2inv*vcr2inv;
      diag_fact=    Cbiot*vcr2inv*dotprod;
      off_fact =-2.*Cbiot*vcr4inv*dotprod;

      Dvcross(0,0)=diag_fact+off_fact*Vcr[0]*Vcr[0];
      Dvcross(1,0)=off_fact*Vcr[0]*Vcr[1];
      Dvcross(1,1)=diag_fact+off_fact*Vcr[1]*Vcr[1];
      Dvcross(2,0)=off_fact*Vcr[0]*Vcr[2];
      Dvcross(2,1)=off_fact*Vcr[1]*Vcr[2];
      Dvcross(2,2)= diag_fact+off_fact*Vcr[2]*Vcr[2];


      // ------------------------------- difference and RAB terms derivatives
      Vsc=Vcr.transpose()*vcr2inv*Cbiot;
      Ddiff=Vsc*RAB;
      dQ_dRAB=Vsc*Tv;


      // ----------------------------------------------------- Final assembly
      dQ_dRA=Dvcross_by_skew3d(Dvcross,-R.row(bb))+Ddiff*Array_Der_runit[aa];
      dQ_dRB=Dvcross_by_skew3d(Dvcross, R.row(aa))-Ddiff*Array_Der_runit[bb];

      DerP += dQ_dRA + dQ_dRB;
      DerVertices[aa] -= dQ_dRAB + dQ_dRA;
      DerVertices[bb] += dQ_dRAB - dQ_dRB;
    }
  }



  void der_biot_panel_map( map_Mat3by3& DerP,
             Vec_map_Mat3by3& DerVertices,
             const map_RowVec3 zetaP,
             const map_Mat4by3 ZetaPanel,
             const double gamma ){
    /*
    This implementation works with mapping objects.
    */


    // declarations
    int ii,aa,bb;
    const double Cbiot=PIquart*gamma;
    double r1inv, vcr2, vcr2inv, vcr4inv, dotprod, diag_fact, off_fact;

    RowVector3d RAB, Vcr, Tv;
    Vector3d Vsc;

    Matrix3d Dvcross, Ddiff, dQ_dRA, dQ_dRB, dQ_dRAB;

    Matrix4by3d R;    // vectors P - vertex matrix
    Matrix4by3d Runit;  // unit vectors P - vertex matrix

    Matrix3d Array_Der_runit[Nvert]; // as a static arrays (we know size)


    // ----------------------------------------------- Compute common variables
    // these are constants or variables depending only on vertices and P coords
    for(ii=0;ii<Nvert;ii++){

      R.row(ii)=zetaP-ZetaPanel.row(ii);

      r1inv=1./R.row(ii).norm();
      Runit.row(ii)=R.row(ii)*r1inv;

      der_runit( Array_Der_runit[ii], R.row(ii), r1inv, -std::pow(r1inv,3) );
    }


    // -------------------------------------------------- Loop through segments
    for(ii=0;ii<Nvert;ii++){

      // vertices indices
      aa=avec[ii];
      bb=bvec[ii];

      // utility vars
      RAB=ZetaPanel.row(bb)-ZetaPanel.row(aa);  // segment vector
      Vcr=R.row(aa).cross(R.row(bb));
      vcr2=Vcr.dot(Vcr);
      if (vcr2<VORTEX_RADIUS_SQ*RAB.dot(RAB)){
        //cout << endl << "Skipping seg. " << ii << endl;
        continue;}
      Tv=Runit.row(aa)-Runit.row(bb);
      dotprod=RAB.dot(Tv);


      // ------------------------------------------ cross-product derivatives
      // lower triangular part only
      vcr2inv=1./vcr2;
      vcr4inv=vcr2inv*vcr2inv;
      diag_fact=    Cbiot*vcr2inv*dotprod;
      off_fact =-2.*Cbiot*vcr4inv*dotprod;

      Dvcross(0,0)=diag_fact+off_fact*Vcr[0]*Vcr[0];
      Dvcross(1,0)=off_fact*Vcr[0]*Vcr[1];
      Dvcross(1,1)=diag_fact+off_fact*Vcr[1]*Vcr[1];
      Dvcross(2,0)=off_fact*Vcr[0]*Vcr[2];
      Dvcross(2,1)=off_fact*Vcr[1]*Vcr[2];
      Dvcross(2,2)= diag_fact+off_fact*Vcr[2]*Vcr[2];


      // ------------------------------- difference and RAB terms derivatives
      Vsc=Vcr.transpose()*vcr2inv*Cbiot;
      Ddiff=Vsc*RAB;
      dQ_dRAB=Vsc*Tv;


      // ----------------------------------------------------- Final assembly
      dQ_dRA=Dvcross_by_skew3d(Dvcross,-R.row(bb))+Ddiff*Array_Der_runit[aa];
      dQ_dRB=Dvcross_by_skew3d(Dvcross, R.row(aa))-Ddiff*Array_Der_runit[bb];

      //cout << endl << "dQ_dRA = " << endl << dQ_dRA << endl;
      DerP += dQ_dRA + dQ_dRB;
      DerVertices[aa] -= dQ_dRAB + dQ_dRA;
      DerVertices[bb] += dQ_dRAB - dQ_dRB;
    }
  /*  cout << "vcr2=" << vcr2 << endl;
    cout << "Tv=" << Tv << endl;
    cout << "dotprod=" << dotprod << endl;
    cout << "dQ_dRB=" << dQ_dRB << endl;
  */
  }


  // -----------------------------------------------------------------------------
  // Sub-functions

  void der_runit(Matrix3d& Der,const RowVector3d& rv, double rinv,double minus_rinv3){
    /*Warning:
    1. RowVector3d needs to defined as constant if in main code RowVector
    is a row of a matrix.
    2. The function will fail is Matrix3d is a sub-block of a matrix.
     */

    // alloc upper diagonal part
    Der(0,0)=rinv+minus_rinv3*rv(0)*rv(0);
    Der(0,1)=     minus_rinv3*rv(0)*rv(1);
    Der(0,2)=     minus_rinv3*rv(0)*rv(2);
    Der(1,1)=rinv+minus_rinv3*rv(1)*rv(1);
    Der(1,2)=     minus_rinv3*rv(1)*rv(2);
    Der(2,2)=rinv+minus_rinv3*rv(2)*rv(2);
    // alloc lower diag
    Der(1,0)=Der(0,1);
    Der(2,0)=Der(0,2);
    Der(2,1)=Der(1,2);
    }



  Matrix3d Dvcross_by_skew3d(const Matrix3d& Dvcross, const RowVector3d& rv){
    /*Warning:
    1. RowVector3d needs to defined as constant if in main code RowVector
    is a row of a matrix.
     */

    Matrix3d P;

    P(0,0)=Dvcross(1,0)*rv(2)-Dvcross(2,0)*rv(1);
    P(0,1)=Dvcross(2,0)*rv(0)-Dvcross(0,0)*rv(2);
    P(0,2)=Dvcross(0,0)*rv(1)-Dvcross(1,0)*rv(0);
    //
    P(1,0)=P(0,1);
    P(1,1)=Dvcross(2,1)*rv(0)-Dvcross(1,0)*rv(2);
    P(1,2)=Dvcross(1,0)*rv(1)-Dvcross(1,1)*rv(0);
    //
    P(2,0)=P(0,2);
    P(2,1)=P(1,2);
    P(2,2)=Dvcross(2,0)*rv(1)-Dvcross(2,1)*rv(0);

    return P;
    }




  // -----------------------------------------------------------------------------


  void dvinddzeta(map_Mat3by3 DerC,
          map_Mat DerV,
          const map_RowVec3 zetaC,
          Vec_map_Mat ZetaIn,
          map_Mat GammaIn,
          int& M_in,
          int& N_in,
          int& Kzeta_in,
          bool& IsBound,
          int& M_in_bound, // M of bound surf associated
          int& Kzeta_in_bound
          )
  {
    int cc, vv, mm, nn, jj, cc_in; //pp
    //int Kin=M_in*N_in;


    // below defined as maps to keep compatibility with der-biot_panel_map
    //Matrix4by3d ZetaPanel_in;
    //Matrix3d derv[Nvert];
    double p_ZetaPanel_in[12];
    double p_derv[36];
    map_Mat4by3 ZetaPanel_in(p_ZetaPanel_in);
    Vec_map_Mat3by3 derv;
    for(vv=0;vv<4;vv++) derv.push_back( map_Mat3by3(p_derv+9*vv) );


  /*  cout << "Kzeta_in=" << endl << Kzeta_in << endl;
    cout << "DerV = " << endl << DerV << endl;
    cout << "GammaIn = " << endl << GammaIn << endl;
    for(cc=0;cc<3;cc++){
      cout << "ZetaIn[" << cc << "] = " << endl <<  ZetaIn[cc] << endl;
    }*/


    if (IsBound){// ------------------------------------------------ Bound case

      // Loop panels (mm,nn)
      for (mm=0; mm<M_in; mm++){
        for (nn=0; nn<N_in; nn++){
          //pp=mm*N_in+nn; // panel no.

          // get panel coords in 4x3 format
          for(cc=0; cc<3; cc++){
            for(vv=0; vv<Nvert; vv++){
              ZetaPanel_in(vv,cc)=ZetaIn[cc](mm+dm[vv],nn+dn[vv]);
            }
          }

          // init. local derivatives
          for(vv=0; vv<Nvert; vv++) derv[vv].setZero();

          // get local deriv
          der_biot_panel_map(DerC,derv,zetaC,ZetaPanel_in,GammaIn(mm,nn));
          //for(vv=0; vv<Nvert; vv++) cout << derv[vv] << endl;

          for(cc=0; cc<3; cc++){
            for(vv=0; vv<Nvert; vv++){
              for(cc_in=0; cc_in<3; cc_in++){
                jj= cc_in*Kzeta_in + (mm+dm[vv])*(N_in+1) + (nn+dn[vv]);
                DerV(cc,jj)+=derv[vv](cc,cc_in);
              }
            }
          }
        }
      }


    } else{ // ------------------------------------------------------ Wake case


      // scan TE first
      mm=0;
      for (nn=0; nn<N_in; nn++){
        //pp=mm*N_in+nn; // panel no.

        // get panel coords in 4x3 format
        for(cc=0; cc<3; cc++){
          for(vv=0; vv<Nvert; vv++){
            ZetaPanel_in(vv,cc)=ZetaIn[cc](mm+dm[vv],nn+dn[vv]);
          }
        }

        // init. local derivatives. only vertices 0 and 3 are on TE
        derv[0].setZero();
        derv[3].setZero();

        // get local deriv
        der_biot_panel_map(DerC,derv,zetaC,ZetaPanel_in,GammaIn(mm,nn));

        for(cc=0; cc<3; cc++){
          for(cc_in=0; cc_in<3; cc_in++){
            // vv=0
            jj= cc_in*Kzeta_in_bound + M_in_bound*(N_in+1) + (nn);
            DerV(cc,jj)+=derv[0](cc,cc_in);
            // vv=3
            jj= cc_in*Kzeta_in_bound + M_in_bound*(N_in+1) + (nn+1);
            DerV(cc,jj)+=derv[3](cc,cc_in);
          }

        }
      }


      // Loop other panels (mm,nn) for colloc point
      for (mm=1; mm<M_in; mm++){
        for (nn=0; nn<N_in; nn++){

          // get panel coords in 4x3 format
          for(cc=0; cc<3; cc++){
            for(vv=0; vv<Nvert; vv++){
              ZetaPanel_in(vv,cc)=ZetaIn[cc](mm+dm[vv],nn+dn[vv]);
            }
          }
          // update DerC
          der_biot_panel_map(DerC,derv,zetaC,ZetaPanel_in,GammaIn(mm,nn));
        }// loop nn
      }// loop mm
    }// if-else
  }




  void aic3(  map_Mat AIC3,
        const map_RowVec3 zetaC,
        Vec_map_Mat ZetaIn,
        int& M_in,
        int& N_in)
  {

    int mm,nn,cc,vv;

    double p_ZetaPanel_in[12];
    map_Mat4by3 ZetaPanel_in(p_ZetaPanel_in);

    double p_vel[3];
    map_RowVec3 vel(p_vel);

    // Loop panels (mm,nn)
    for (mm=0; mm<M_in; mm++){
      for (nn=0; nn<N_in; nn++){
        //pp=mm*N_in+nn; // panel no.

        // get panel coords in 4x3 format
        for(cc=0; cc<3; cc++){
          for(vv=0; vv<Nvert; vv++){
            ZetaPanel_in(vv,cc)=ZetaIn[cc](mm+dm[vv],nn+dn[vv]);
          }
        }

        vel.setZero();
        biot_panel_map( vel, zetaC, ZetaPanel_in, 1.0);
        AIC3.col(mm*N_in+nn)=vel;

      }
    }
  }



  void ind_vel(map_RowVec3 velC,
        const map_RowVec3 zetaC,
        Vec_map_Mat ZetaIn,
        map_Mat GammaIn,
        int& M_in,
        int& N_in)
  {

    int mm,nn,cc,vv;

    double p_ZetaPanel_in[12];
    map_Mat4by3 ZetaPanel_in(p_ZetaPanel_in);

    // Loop panels (mm,nn)
    for (mm=0; mm<M_in; mm++){
      for (nn=0; nn<N_in; nn++){
        //pp=mm*N_in+nn; // panel no.

        // get panel coords in 4x3 format
        for(cc=0; cc<3; cc++){
          for(vv=0; vv<Nvert; vv++){
            ZetaPanel_in(vv,cc)=ZetaIn[cc](mm+dm[vv],nn+dn[vv]);
          }
        }

        biot_panel_map( velC, zetaC, ZetaPanel_in, GammaIn(mm,nn));
      }
    }
  }
}
