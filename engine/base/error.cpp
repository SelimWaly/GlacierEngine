//  **************************************
//  File:        error.cpp
//  ***************************************


#include "NE_pubhead.h"
#include "NE_error.h"

KNRESULT g_LatestErrorCode = RESULT_OK;

// 
KNRESULT GetLastErrorCode()
{
    return g_LatestErrorCode;
}

// 
void SetLastErrorCode(KNRESULT theErrorCode)
{
    g_LatestErrorCode = theErrorCode;
}

kn_bool operator==(const KNRESULT& lhs, const KNRESULT& rhs)
{
    if (lhs.dwclass == rhs.dwclass && lhs.dwCode == rhs.dwCode && lhs.dwComponent == rhs.dwComponent && lhs.dwFacility == rhs.dwFacility)
    {
        return true;
    }
    else
    {
        return false;
    }
}

kn_bool operator!=(const KNRESULT& lhs, const KNRESULT& rhs)
{
    return !(lhs == rhs);
}
