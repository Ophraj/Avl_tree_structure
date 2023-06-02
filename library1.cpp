//
// Created by ophra on 29/11/2021.
//

#include "library1.h"
#include "CompaniesManager.h"

void* Init()
{
    CompaniesManager* DS = new CompaniesManager();
    return (void*)DS;
}

StatusType AddCompany(void *DS, int CompanyID, int Value){
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->AddCompany_C(CompanyID, Value);
}

StatusType AddEmployee(void *DS, int EmployeeID, int CompanyID, int Salary, int Grade)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->AddEmployee_C(EmployeeID, CompanyID, Salary, Grade);
}

StatusType RemoveCompany(void *DS, int CompanyID){
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->RemoveCompany_C(CompanyID);
}


StatusType RemoveEmployee(void *DS, int EmployeeID)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->RemoveEmployee_C(EmployeeID);
}

StatusType GetCompanyInfo(void *DS, int CompanyID, int *Value, int *NumEmployees)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->GetCompanyInfo_C(CompanyID, Value, NumEmployees);
}

StatusType GetEmployeeInfo(void *DS, int EmployeeID, int *EmployerID, int *Salary, int *Grade)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->GetEmployeeInfo_C(EmployeeID, EmployerID, Salary, Grade);
}

StatusType IncreaseCompanyValue(void *DS, int CompanyID, int ValueIncrease)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->IncreaseCompanyValue_C(CompanyID, ValueIncrease);
}

StatusType PromoteEmployee(void *DS, int EmployeeID, int SalaryIncrease, int BumpGrade)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->PromoteEmployee_C(EmployeeID, SalaryIncrease, BumpGrade);
}

StatusType HireEmployee(void *DS, int EmployeeID, int NewCompanyID)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->HireEmployee_C(EmployeeID, NewCompanyID);
}

StatusType AcquireCompany(void *DS, int AcquirerID, int TargetID, double Factor)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->AcquireCompany_C(AcquirerID, TargetID, Factor);
}

StatusType GetHighestEarner(void *DS, int CompanyID, int *EmployeeID)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->GetHighestEarner_C(CompanyID, EmployeeID);
}

StatusType GetAllEmployeesBySalary(void *DS, int CompanyID, int **Employees, int *NumOfEmployees)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->GetAllEmployeesBySalary_C(CompanyID, Employees, NumOfEmployees);
}

StatusType GetHighestEarnerInEachCompany(void *DS, int NumOfCompanies, int **Employees)
{
    if(DS == nullptr)
    {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*)DS)->GetHighestEarnerInEachCompany_C(NumOfCompanies, Employees);
}

StatusType GetNumEmployeesMatching(void *DS, int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                   int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees) {
    if (DS == nullptr) {
        return INVALID_INPUT;
    }
    return ((CompaniesManager*) DS)->GetNumEmployeesMatching_C(CompanyID, MinEmployeeID,MaxEmployeeId,
                                                               MinSalary, MinGrade, TotalNumOfEmployees, NumOfEmployees );
}

void Quit(void** DS)
{
    (*((CompaniesManager**)DS))->Quit_C();
    delete (CompaniesManager*)*DS;
    *DS = nullptr;
}