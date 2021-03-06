#include <iostream>
#include "Interp4Set.hh"

using std::cout;
using std::endl;


extern "C" {
 Interp4Command* CreateCmd(void);
  const char* GetCmdName() { return "Set"; }
}




/*!
 * \brief
 *
 *
 */
Interp4Command* CreateCmd(void)
{
  return Interp4Set::CreateCmd();
}


/*!
 *
 */
Interp4Set::Interp4Set(): 
  coordinates_x(0),
  coordinates_y(0),
  angle_OX(0),
  angle_OY(0),
  angle_OZ(0)
{}


/*!
 *
 */
void Interp4Set::PrintCmd() const
{
  cout << GetCmdName() << " Obj_A " << coordinates_x << " " << coordinates_y << " "  << angle_OX << " "  << angle_OY << " "  << angle_OZ << " "  << endl;
}


/*!
 *
 */
const char* Interp4Set::GetCmdName() const
{
  return ::GetCmdName();
}


/*!
 *
 */
bool Interp4Set::ExecCmd( MobileObj  *pMobObj,  AccessControl *pAccCtrl) const
{
  pAccCtrl->LockAccess();

  Vector3D new_position = pMobObj->GetPositoin_m();
  new_position[0] = this->coordinates_x;
  new_position[1] = this->coordinates_y;
  pMobObj->SetPosition_m(new_position);

  pMobObj->SetAng_Pitch_deg(angle_OY);
  pMobObj->SetAng_Roll_deg(angle_OX);
  pMobObj->SetAng_Yaw_deg(angle_OZ);

  pAccCtrl->MarkChange();
  pAccCtrl->UnlockAccess();
  usleep(300000);

  return true;
}


/*!
 *
 */
bool Interp4Set::ReadParams(std::istream& Strm_CmdsList)
{
  Strm_CmdsList >> coordinates_x >> coordinates_y >> angle_OX >> angle_OY >> angle_OZ;
  return !Strm_CmdsList.fail();
}


/*!
 *
 */
Interp4Command* Interp4Set::CreateCmd()
{
  return new Interp4Set();
}


/*!
 *
 */
void Interp4Set::PrintSyntax() const
{
  cout << "   Set  NazwaObiektu  wsp_x[m]  wsp_y[m]  kat_OX[deg]  kat_OY[deg]  kat_OZ[deg]" << endl;
}
