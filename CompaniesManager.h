//
// Created by ophra on 20/04/2022.
//

#ifndef EMPLOYEE1_COMPANIESMANAGER_H
#define EMPLOYEE1_COMPANIESMANAGER_H


#include "Avl_tree.h"
#include "library1.h"

//typedef enum {
//    SUCCESS = 0,
//    FAILURE = -1,
//    ALLOCATION_ERROR = -2,
//    INVALID_INPUT = -3
//} StatusType;

typedef struct employee_in_company_t *Employee_in_company;
typedef struct employee_t *Employee;
typedef struct company_t *Company;
typedef struct employee_by_salary_t *Employee_by_salary;
typedef struct company_not_empty_t *Company_not_empty;

template<class T>
int GetEmployeeID(T element);

int CompanyInorder(Node<Company_not_empty>* node, int** array, int numofCompanies);
int CompanyInorderArray(Node<Employee_in_company>* node, Node<Employee_in_company> **array, int i);
int CompareEmployees (Node<Employee_in_company>* pl1, Node<Employee_in_company>* pl2);
//void BuildEmptyTree(Avl_tree<Employee_in_company>* tree, int num_of_nodes, Node<Employee_in_company>* root, int i);
//int FillTree(Avl_tree<Employee_in_company>* tree, Node<Employee_in_company>* array, int i, Node<Employee_in_company>* root);
void FillTreeNew(Avl_tree<Employee_in_company>* tree, Node<Employee_in_company>* array, Node<Employee_in_company> root, int i);
void UpdateCompanyAndHeight(Node<Employee_in_company>* node , Node<Company>* company);
void UpdateFather(Node<Employee_in_company>* node);
//void RemoveInorderNodes(Node<Company>* node);
void RemoveInorderTree(Node<Company>* node);
//int CountOfCompanyNotEmpty(Node<Company_not_empty>* node, int* i);


class CompaniesManager {
    Avl_tree<Company>* COMPANIES;
    Avl_tree<Employee>* EMPLOYEES_ID;
    Avl_tree<Employee_by_salary>* EMPLOYEES_SALARY;
    Avl_tree<Company_not_empty>* COMPANY_NOT_EMPTY;
    Node<Company>* Highest_earner_in_DS;
    int num_of_companies_not_empty;

public:
    CompaniesManager();

    ~CompaniesManager();

    //Function to make

    StatusType AddCompany_C(int CompanyID, int Value);

    StatusType AddEmployee_C(int EmployeeID, int CompanyID, int Salary, int Grade);

    StatusType RemoveEmployee_C(int EmployeeID);

    StatusType RemoveCompany_C(int CompanyID);

    StatusType GetCompanyInfo_C(int CompanyID, int *Value, int *NumEmployees);

    StatusType GetEmployeeInfo_C(int EmployeeID, int *EmployerID, int *Salary, int *Grade);

    StatusType IncreaseCompanyValue_C(int CompanyID, int ValueIncrease);

    StatusType PromoteEmployee_C(int EmployeeID, int SalaryIncrease, int BumpGrade);

    StatusType HireEmployee_C(int EmployeeID, int NewCompanyID);

    StatusType AcquireCompany_C(int AcquirerID, int TargetID, double Factor);

    StatusType GetHighestEarner_C(int CompanyID, int *EmployeeID);

    StatusType GetAllEmployeesBySalary_C(int CompanyID, int **Employees, int *NumOfEmployees);

    StatusType GetHighestEarnerInEachCompany_C(int NumOfCompanies, int **Employees);

    StatusType GetNumEmployeesMatching_C(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                         int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees);

    void Quit_C();
};

#endif //EMPLOYEE1_COMPANIESMANAGER_H
