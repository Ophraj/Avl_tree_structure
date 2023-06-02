//
// Created by ophra on 20/04/2022.
//

#include <ctime>
#include <new>
#include <math.h>
#include "CompaniesManager.h"
#include <cstdlib>

//------------------------------Elements---------------------------------
struct employee_in_company_t{
    int EmployeeID;
    int grade;
    Node<company_t*>* company;
};

struct employee_t{
    Node<employee_in_company_t*>* ptr_employee_company_salary;
    Node<employee_by_salary_t*>* ptr_employee_salary;
};

struct company_t{
    int num_of_employees;
    int value;
    Node<employee_in_company_t*>* em_with_highest_salary;
    Avl_tree<employee_in_company_t*>* tree_of_employees_in_company;
    Avl_tree<employee_t*>* tree_of_employees_in_company_id;
};

struct employee_by_salary_t{
    int EmployeeID;
    Node<employee_in_company_t*>* ptr_employee_salary_company;
    Node<employee_t*>* ptr_employer_id;
};

struct company_not_empty_t{
    Node<company_t*>* company;
};

template<class T>
int GetPlayerID(T element){
    if(element == nullptr)
        return 0;

    Employee_by_salary temp;
    if(typeid(element) == typeid(temp))
    {
        temp = (Employee_by_salary)element;
        return temp->EmployeeID;
    }

    Employee_in_company temp2;
    if(typeid(element) == typeid(temp2))
    {
        temp2 = (Employee_in_company)element;
        return temp2->EmployeeID;
    }

    return -1;
}

//********************************** FunctionsToHelp ********************************************

void UpdateCompanyAndHeight(Node<Employee_in_company>* node , Node<Company>* company)
{
    if(node == nullptr)
    {
        return;
    }

    UpdateCompanyAndHeight(node->GetNodeLeft(), company);
    UpdateCompanyAndHeight(node->GetNodeRight(), company);
    node->GetElement()->company = company;
    node->SetNewHeight();
}

void UpdateHeight(Node<Employee>* node)
{
    if(node == nullptr)
    {
        return;
    }

    UpdateHeight(node->GetNodeLeft());
    UpdateHeight(node->GetNodeRight());
    node->SetNewHeight();
}

void UpdateFather(Node<Employee_in_company>* node){
    if(node == nullptr)
    {
        return;
    }

    if(node->GetNodeLeft() != nullptr)
    {
        node->GetNodeLeft()->SetFatherNode(node);
    }
    if(node->GetNodeRight() != nullptr)
    {
        node->GetNodeRight()->SetFatherNode(node);
    }
    UpdateFather(node->GetNodeLeft());
    UpdateFather(node->GetNodeRight());
}

void UpdateFatherID(Node<Employee>* node){
    if(node == nullptr)
    {
        return;
    }

    if(node->GetNodeLeft() != nullptr)
    {
        node->GetNodeLeft()->SetFatherNode(node);
    }
    if(node->GetNodeRight() != nullptr)
    {
        node->GetNodeRight()->SetFatherNode(node);
    }
    UpdateFatherID(node->GetNodeLeft());
    UpdateFatherID(node->GetNodeRight());
}

int CompanyInorderArray(Node<Employee_in_company>* node, Node<Employee_in_company> **array, int i)
{
    if (node== nullptr)
        return i;

    int left = CompanyInorderArray(node->GetNodeLeft(), array, i);

    array[left]= node;

    int right = CompanyInorderArray(node->GetNodeRight(), array, left+1);
    return right;
}

int CompanyInorderArrayID(Node<Employee>* node, Node<Employee> **array, int i)
{
    if (node== nullptr)
        return i;

    int left = CompanyInorderArrayID(node->GetNodeLeft(), array, i);

    array[left]= node;

    int right = CompanyInorderArrayID(node->GetNodeRight(), array, left+1);
    return right;
}

int CompareEmployees (Node<Employee_in_company>* em1, Node<Employee_in_company>* em2){

    if (em1->GetKey() < em2->GetKey())
        return -1;

    if (em1->GetKey()==em2->GetKey())
    {
        if(em1->GetElement()->EmployeeID > em2->GetElement()->EmployeeID)
            return -1;
        else
            return 1;
    }
    return 1;
}

int CompanyInorder(Node<Company_not_empty>* node, int** array,int numofCompanies) {

    if (node == nullptr)
        return 1;

    int i = 0;
    for (; i < numofCompanies; i++) {
        if(node== nullptr)
            break;

        (*(array))[i] = node->GetElement()->company->GetElement()->em_with_highest_salary->GetElement()->EmployeeID;
        node = node->Get_Following_node();
    }

    if (i<numofCompanies)
    {
        return 0;
    }
    return 1;
}

void RemoveInorderTree(Node<Company>* node)
{
    if(node == nullptr)
        return;

    RemoveInorderTree(node->GetNodeLeft());
    RemoveInorderTree(node->GetNodeRight());
    node->GetElement()->tree_of_employees_in_company->AuxDistructorTree(node->GetElement()->tree_of_employees_in_company->GetRoot());
    node->GetElement()->tree_of_employees_in_company_id->AuxDistructorTree(node->GetElement()->tree_of_employees_in_company_id->GetRoot());

    delete node->GetElement()->tree_of_employees_in_company;
    delete node->GetElement()->tree_of_employees_in_company_id;
}

//----------------------------Manager-----------------------------

CompaniesManager::CompaniesManager()
{
    try {
        COMPANIES = new Avl_tree<Company>;
    }
    catch (std::bad_alloc &) {
        throw ;
    }
    try {
        EMPLOYEES_ID = new Avl_tree<Employee>;
    }
    catch (std::bad_alloc &) {
        delete COMPANIES;
        throw ;
    }
    try {
        EMPLOYEES_SALARY = new Avl_tree<Employee_by_salary>;
    }
    catch (std::bad_alloc &) {
        delete COMPANIES;
        delete EMPLOYEES_ID;
        throw ;
    }
    try {
        COMPANY_NOT_EMPTY = new Avl_tree<Company_not_empty>;
    }
    catch (std::bad_alloc &) {
        delete COMPANIES;
        delete EMPLOYEES_ID;
        delete EMPLOYEES_SALARY;
        throw ;
    }
    Highest_earner_in_DS= nullptr;
    num_of_companies_not_empty = 0;
}

CompaniesManager::~CompaniesManager()
{
    delete COMPANIES;
    delete EMPLOYEES_ID;
    delete EMPLOYEES_SALARY;
    delete COMPANY_NOT_EMPTY;
}

StatusType CompaniesManager::AddCompany_C(int CompanyID, int Value)
{
    if(CompanyID <= 0 || Value<=0)
    {
        return INVALID_INPUT;
    }

    Node<Company>* group=this->COMPANIES->FindNode(COMPANIES->GetRoot(), CompanyID);
    if (group!= nullptr)
        return FAILURE;

    Company new_element = new company_t;
    new_element->tree_of_employees_in_company = new Avl_tree<Employee_in_company>();
    new_element->tree_of_employees_in_company_id = new Avl_tree<Employee>();
    new_element->num_of_employees = 0;
    new_element->value= Value;
    new_element->em_with_highest_salary = nullptr;

    AVLResults res = this->COMPANIES->InsertNode(CompanyID, new_element, nullptr);

    if (res == AVL_NO_ALLOCATION)
    {
        delete new_element->tree_of_employees_in_company;
        delete new_element->tree_of_employees_in_company_id;
        delete new_element;
        // null_arg
    }
    return SUCCESS;
}

StatusType CompaniesManager::AddEmployee_C(int EmployeeID, int CompanyID, int Salary, int Grade) {
    {

        if (EmployeeID <= 0 || CompanyID <= 0 || Salary <= 0 || Grade < 0)
            return INVALID_INPUT;


        //If the player exists return FAILURE
        Avl_tree<Employee>* Avl_employees = this->EMPLOYEES_ID;
        Node<Employee> *employee_to_add = Avl_employees->FindNode(Avl_employees->GetRoot(), EmployeeID);
        if (employee_to_add != nullptr)
            return FAILURE;

        //if the group doesn't exist return FAILURE
        Avl_tree<Company>* AvlCompany = this->COMPANIES;
        Node<Company>* company_to_add = AvlCompany->FindNode(AvlCompany->GetRoot(), CompanyID);
        if (company_to_add == nullptr)
            return FAILURE;

        //The company exists

        //If there wasn't any employee before, add the company to the tree "not empty"
        if(company_to_add->GetElement()->num_of_employees == 0)
        {
            Company_not_empty element_group_not_empty = new company_not_empty_t;
            element_group_not_empty->company = company_to_add;

            this->COMPANY_NOT_EMPTY->InsertNode(company_to_add->GetKey(), element_group_not_empty, nullptr);
            this->num_of_companies_not_empty += 1;
        }

        //We want to add the player to the company in COMPANIES tree
        //Create the type/element of the new "employee in company" in order to insert it.
        Employee_in_company em_in_company = nullptr;
        try {
            em_in_company = new employee_in_company_t;
        }
        catch (std::bad_alloc &) {
            return ALLOCATION_ERROR;
        }

        em_in_company->EmployeeID= EmployeeID;
        em_in_company->company= company_to_add;
        em_in_company->grade= Grade;

        //The element of employee_in_company is created we can add it
        Company company1_element = (Company) (company_to_add->GetElement());

        //Add the employee_in_company to the tree of the company
        bool was_empty=false;
        if(company1_element->tree_of_employees_in_company->GetRoot() == nullptr) //tree is empty
        {
            was_empty=true;
        }

        Avl_tree<Employee_in_company>* em_in_company_tree = company1_element->tree_of_employees_in_company;

        if (em_in_company_tree->InsertNode(Salary, em_in_company, EmployeeID, nullptr) != AVL_SUCCESS)
            return ALLOCATION_ERROR;
        Node<Employee_in_company>* em_in_company_node = em_in_company_tree->FindNode(em_in_company_tree->GetRoot(), Salary, EmployeeID);


        //Add the employee in the second tree of company (id tree)
        Employee em_in_company_id = nullptr;
        try {
            em_in_company_id = new employee_t;
        }
        catch (std::bad_alloc &) {
            delete em_in_company;
            return ALLOCATION_ERROR;
        }

        em_in_company_id->ptr_employee_company_salary= em_in_company_node;
        em_in_company_id->ptr_employee_salary= nullptr;

        Avl_tree<Employee>* em_in_company_id_tree = company1_element->tree_of_employees_in_company_id;

        if (em_in_company_id_tree->InsertNode(EmployeeID, em_in_company_id, nullptr) != AVL_SUCCESS)
            return ALLOCATION_ERROR;

        //UPDATE highest_earner_in_group
        if (was_empty == 1) {  //check if it's the first player in the group
            company1_element->em_with_highest_salary = em_in_company_node;
        }

        else {
            if (Salary > company1_element->em_with_highest_salary->GetKey())
                company1_element->em_with_highest_salary = em_in_company_node;

            else if (Salary == company1_element->em_with_highest_salary->GetKey()) {
                Employee_in_company element_em_highest = (Employee_in_company) company1_element->em_with_highest_salary->GetElement();
                if (element_em_highest->EmployeeID > EmployeeID)
                    company1_element->em_with_highest_salary = em_in_company_node;
            }
        }

        company1_element->num_of_employees += 1;

        //Update Get Highest Group
        bool first_player_ever= false;
        if(this->Highest_earner_in_DS == nullptr) //it's the first player ever
        {
            this->Highest_earner_in_DS = company_to_add;
            first_player_ever=true;
        }

        Node<Company>* company_with_highest_employee= this->Highest_earner_in_DS;
        if (first_player_ever== false && company_with_highest_employee!=company_to_add)
        {
            Company company_element_highest= (Company) company_with_highest_employee->GetElement();

            if (company1_element->em_with_highest_salary->GetKey() > company_element_highest->em_with_highest_salary->GetKey())
            {
                this->Highest_earner_in_DS = company_to_add;
            }

            else if (company1_element->em_with_highest_salary->GetKey() == company_element_highest->em_with_highest_salary->GetKey())
            {
                Employee_in_company element_employee_company1 =(Employee_in_company) company1_element->em_with_highest_salary->GetElement();
                Employee_in_company element_employee_highest =(Employee_in_company) company_element_highest->em_with_highest_salary->GetElement();

                if (element_employee_company1->EmployeeID < element_employee_highest->EmployeeID)
                {
                    this->Highest_earner_in_DS = company_to_add;
                }
            }
        }

        //Now we'll add the players in the 2 trees
        //Create the pl_by_level
        Employee_by_salary em_by_salary = nullptr;
        try {
            em_by_salary = new employee_by_salary_t;
        }
        catch (std::bad_alloc &) {
            delete company1_element->tree_of_employees_in_company;
            delete em_in_company;
            delete em_in_company_id;
            return ALLOCATION_ERROR;
        }

        em_by_salary->EmployeeID = EmployeeID;
        em_by_salary->ptr_employee_salary_company = em_in_company_node;

        //pointer to player id needs the node so we create it before

        Avl_tree<Employee_by_salary>* Employee_Salary_Tree = this->EMPLOYEES_SALARY;
        //Node<Player_by_level>* player_level_node = nullptr;
        if (Employee_Salary_Tree->InsertNode(Salary, em_by_salary, EmployeeID, nullptr) != AVL_SUCCESS) {
            delete company1_element->tree_of_employees_in_company;
            delete em_in_company;
            delete em_by_salary;
            delete em_in_company_id;
            return ALLOCATION_ERROR;
        }

        Node<Employee_by_salary>* em_by_salary_node = Employee_Salary_Tree->FindNode(Employee_Salary_Tree->GetRoot(), Salary, EmployeeID);

        Employee employee;
        try {
            employee = new employee_t;
        }
        catch (std::bad_alloc &) {
            delete company1_element->tree_of_employees_in_company;
            delete em_in_company;
            delete em_by_salary;
            delete em_in_company_id;
            return ALLOCATION_ERROR;
        }

        employee->ptr_employee_company_salary = em_in_company_node;
        employee->ptr_employee_salary = em_by_salary_node;

        Avl_tree<Employee>* EmployeesTree = this->EMPLOYEES_ID;
        //Node<Player>* player_node = nullptr;

        if (EmployeesTree->InsertNode(EmployeeID, employee, nullptr) != AVL_SUCCESS) {
            delete company1_element->tree_of_employees_in_company;
            delete em_in_company;
            delete employee;
            delete em_by_salary;
            delete em_in_company_id;
            return ALLOCATION_ERROR;
        }

        Node<Employee>* em_id_node = this->EMPLOYEES_ID->FindNode(EMPLOYEES_ID->GetRoot(), EmployeeID);
        em_by_salary_node->GetElement()->ptr_employer_id = em_id_node;

        return SUCCESS;
    }
}

StatusType CompaniesManager::RemoveEmployee_C(int EmployeeID)
{
    if(EmployeeID <= 0)
    {
        return INVALID_INPUT;
    }

    Node<Employee>* node_to_remove = this->EMPLOYEES_ID->FindNode(this->EMPLOYEES_ID->GetRoot(), EmployeeID);

    //if the employee doesnt exist return FAILURE
    if(node_to_remove == nullptr)
    {
        return FAILURE;
    }

    if(node_to_remove->GetElement()->ptr_employee_company_salary->GetElement()->company->GetElement()->num_of_employees == 1)
    {
        COMPANY_NOT_EMPTY->RemoveNode(node_to_remove->GetElement()->ptr_employee_company_salary->GetElement()->company->GetKey());
        this->num_of_companies_not_empty -= 1;
    }

    //check if the player with playerID is the highest player in game
    if(EmployeeID == this->Highest_earner_in_DS->GetElement()->em_with_highest_salary->GetElement()->EmployeeID)
    {
        Node<Employee_by_salary>* em_by_salary = node_to_remove->GetElement()->ptr_employee_salary;
        if(em_by_salary->GetFatherNode() == nullptr && em_by_salary->GetNodeLeft() == nullptr && em_by_salary->GetNodeRight() == nullptr)
        {
            this->Highest_earner_in_DS = nullptr;
        }
        else
        {
            bool follow_exists = false;
            Node<Employee_by_salary>* following = em_by_salary->Get_Following_node();
            if(following != nullptr)
            {
                this->Highest_earner_in_DS = em_by_salary->Get_Following_node()->GetElement()->ptr_employee_salary_company->GetElement()->company;
                follow_exists = true;
            }

            Node<Employee_by_salary>* previous = em_by_salary->GetPreviousNode();
            if(follow_exists == false && previous != nullptr)
            {
                this->Highest_earner_in_DS = em_by_salary->GetPreviousNode()->GetElement()->ptr_employee_salary_company->GetElement()->company;
            }
        }
    }


    //check if the employee with the employeeID is the employee with highest level
    Node<Employee_in_company >* em_in_company_node = node_to_remove->GetElement()->ptr_employee_company_salary;
    Node<Company>* group_node = em_in_company_node->GetElement()->company;

    if(group_node->GetElement()->em_with_highest_salary->GetElement()->EmployeeID == EmployeeID)
    {
        if(em_in_company_node->GetElement()->company->GetElement()->num_of_employees == 1)
        {
            group_node->GetElement()->em_with_highest_salary = nullptr;
        }
        else
        {
            bool follow_exists = false;
            Node<Employee_in_company>* following = em_in_company_node->Get_Following_node();
            if(following != nullptr)
            {
                group_node->GetElement()->em_with_highest_salary = following;
                follow_exists = true;
            }

            Node<Employee_in_company>* previous = em_in_company_node->GetPreviousNode();
            if(follow_exists == false && previous != nullptr)
            {
                group_node->GetElement()->em_with_highest_salary = previous;
            }
        }
    }

    //-1 from number of employees
    group_node->GetElement()->num_of_employees -= 1;

    //delete the employee from tree of employees in company salary
    if(group_node->GetElement()->tree_of_employees_in_company->RemoveNode(em_in_company_node->GetKey(), EmployeeID) != AVL_SUCCESS)
    {
        return FAILURE;
    }

    //delete the employee from the tree of employees in company id
    if(group_node->GetElement()->tree_of_employees_in_company_id->RemoveNode(EmployeeID) != AVL_SUCCESS)
    {
        return FAILURE;
    }

    //delete from employees by salary
    if(this->EMPLOYEES_SALARY->RemoveNode(node_to_remove->GetElement()->ptr_employee_salary->GetKey(), node_to_remove->GetElement()->ptr_employee_salary->GetElement()->EmployeeID) != AVL_SUCCESS)
    {
        return FAILURE;
    }

    //delete from employees by id
    if(this->EMPLOYEES_ID->RemoveNode(node_to_remove->GetKey()) != AVL_SUCCESS)
    {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType CompaniesManager::RemoveCompany_C(int CompanyID) {
    if(CompanyID <= 0){
        return INVALID_INPUT;
    }
    Node<Company>* node_to_remove = this->COMPANIES->FindNode(this->COMPANIES->GetRoot(), CompanyID);
    if(!node_to_remove){
        return FAILURE;
    }
    if(node_to_remove->GetElement()->num_of_employees != 0){
        return FAILURE;
    }
    delete node_to_remove->GetElement()->tree_of_employees_in_company;
    delete node_to_remove->GetElement()->tree_of_employees_in_company_id;
    this->COMPANIES->RemoveNode(CompanyID);
    return SUCCESS;
}

StatusType CompaniesManager::GetCompanyInfo_C(int CompanyID, int *Value, int *NumEmployees) {
    if(CompanyID <= 0 || !Value || !NumEmployees){
        return INVALID_INPUT;
    }
    Node<Company>* company_node = this->COMPANIES->FindNode(this->COMPANIES->GetRoot(), CompanyID);
    if(!company_node){
        return FAILURE;
    }
    *Value = company_node->GetElement()->value;
    *NumEmployees = company_node->GetElement()->num_of_employees;
    return SUCCESS;
}

StatusType CompaniesManager::GetEmployeeInfo_C(int EmployeeID, int *EmployerID, int *Salary, int *Grade) {
    if(EmployeeID <= 0 || !EmployerID || !Salary || !Grade){
        return INVALID_INPUT;
    }
    Node<Employee>* employee_node = this->EMPLOYEES_ID->FindNode(this->EMPLOYEES_ID->GetRoot(), EmployeeID);
    if(!employee_node){
        return FAILURE;
    }
    *EmployerID = employee_node->GetElement()->ptr_employee_company_salary->GetElement()->company->GetKey();
    *Salary = employee_node->GetElement()->ptr_employee_salary->GetKey();
    *Grade = employee_node->GetElement()->ptr_employee_company_salary->GetElement()->grade;
    return SUCCESS;
}

StatusType CompaniesManager::IncreaseCompanyValue_C(int CompanyID, int ValueIncrease) {
    if(CompanyID <= 0 || ValueIncrease <= 0){
        return INVALID_INPUT;
    }
    Node<Company>* company_node = this->COMPANIES->FindNode(this->COMPANIES->GetRoot(), CompanyID);
    if(!company_node){
        return FAILURE;
    }
    company_node->GetElement()->value += ValueIncrease;
    return SUCCESS;
}

StatusType CompaniesManager::PromoteEmployee_C(int EmployeeID, int SalaryIncrease, int BumpGrade) {
    if (EmployeeID <= 0 || SalaryIncrease <= 0) {
        return INVALID_INPUT;
    }

    //If employee doesnt exist, return FAILURE
    Node<Employee> *node_employee_id = this->EMPLOYEES_ID->FindNode(this->EMPLOYEES_ID->GetRoot(), EmployeeID);
    if (node_employee_id == nullptr) {
        return FAILURE;
    }

    //Create the new element of the employee_in_company
    Node<Employee_in_company> *ptr_node_employee_in_company = node_employee_id->GetElement()->ptr_employee_company_salary;
    Employee_in_company new_element_employee_in_company = new employee_in_company_t;
    new_element_employee_in_company->company = ptr_node_employee_in_company->GetElement()->company;
    new_element_employee_in_company->EmployeeID = ptr_node_employee_in_company->GetElement()->EmployeeID;
    int current_grade = ptr_node_employee_in_company->GetElement()->grade;
    if (BumpGrade > 0)
        current_grade++;
    new_element_employee_in_company->grade = current_grade;


    //Keep the company we're in
    Node<Company>* company_of_employee= ptr_node_employee_in_company->GetElement()->company;

    //Keep the highest in game
    int current_highest_salary_in_game = this->Highest_earner_in_DS->GetElement()->em_with_highest_salary->GetKey();
    int current_highest_id_in_game = this->Highest_earner_in_DS->GetElement()->em_with_highest_salary->GetElement()->EmployeeID;

    //Keep the highest in group
    int current_highest_salary_in_company = company_of_employee->GetElement()->em_with_highest_salary->GetKey();
    int current_highest_id_in_company = company_of_employee->GetElement()->em_with_highest_salary->GetElement()->EmployeeID;

    //Calculate the new salary of the employee
    int current_salary = ptr_node_employee_in_company->GetKey();
    int key = SalaryIncrease + current_salary;

    //Remove the last node and add the new one in tree salary of company
    Avl_tree<Employee_in_company> *tree = company_of_employee->GetElement()->tree_of_employees_in_company;
    tree->RemoveNode(current_salary, EmployeeID);
    tree->InsertNode(key, new_element_employee_in_company, EmployeeID, nullptr);
    //keep pointer to the new node
    Node<Employee_in_company> *new_employee_salary_company = tree->FindNode(tree->GetRoot(), key, EmployeeID);

    //Create the new element of employee by salary
    Employee_by_salary new_element_employee_salary = new employee_by_salary_t;
    new_element_employee_salary->ptr_employee_salary_company = new_employee_salary_company;
    new_element_employee_salary->EmployeeID = new_employee_salary_company->GetElement()->EmployeeID;
    new_element_employee_salary->ptr_employer_id = node_employee_id;

    //Remove the last node and add the new one in tree of salaries
    Avl_tree<Employee_by_salary> *tree_salary = this->EMPLOYEES_SALARY;
    tree_salary->RemoveNode(current_salary, EmployeeID);
    tree_salary->InsertNode(key, new_element_employee_salary, EmployeeID, nullptr);
    //Keep the pointer of the new employee in salary tree
    Node<Employee_by_salary> *new_salary_employee = tree_salary->FindNode(tree_salary->GetRoot(), key, EmployeeID);

    //change the pointer of employer id
    node_employee_id->GetElement()->ptr_employee_salary = new_salary_employee;
    node_employee_id->GetElement()->ptr_employee_company_salary = new_employee_salary_company;
    //Change the pointer of employee_id_company
    Avl_tree<Employee>* tree_id = company_of_employee->GetElement()->tree_of_employees_in_company_id;
    Node <Employee>* employee_company_id = tree_id->FindNode(tree_id->GetRoot(), EmployeeID);
    employee_company_id->GetElement()->ptr_employee_company_salary=new_employee_salary_company;

    //Update the highest in group
    if (current_highest_salary_in_company < new_employee_salary_company->GetKey()) {
        company_of_employee->GetElement()->em_with_highest_salary = new_employee_salary_company;
    }
    else if (current_highest_salary_in_company == new_employee_salary_company->GetKey()) {
        if (current_highest_id_in_company > EmployeeID) {
            company_of_employee->GetElement()->em_with_highest_salary = new_employee_salary_company;
        }
    }

    //Update the highest in game
    if (current_highest_salary_in_game < new_employee_salary_company->GetKey()) {
        this->Highest_earner_in_DS = new_employee_salary_company->GetElement()->company;
    }
    else if (current_highest_salary_in_game == new_employee_salary_company->GetKey()) {
        if (current_highest_id_in_game > EmployeeID) {
            this->Highest_earner_in_DS = company_of_employee;
        }
    }

    return SUCCESS;
}

StatusType CompaniesManager::HireEmployee_C(int EmployeeID, int NewCompanyID) {

    if(EmployeeID <= 0 || NewCompanyID <= 0){
        return INVALID_INPUT;
    }
    Node<Employee>* employee_node = this->EMPLOYEES_ID->FindNode(this->EMPLOYEES_ID->GetRoot(), EmployeeID);
    Node<Company>* new_company_node = this->COMPANIES->FindNode(this->COMPANIES->GetRoot(), NewCompanyID);

    if(!employee_node || !new_company_node){
        return FAILURE;
    }

    Node<Company>* last_company = employee_node->GetElement()->ptr_employee_company_salary->GetElement()->company;
    if(last_company->GetKey() == NewCompanyID){
        return FAILURE;
    }

    int salary = employee_node->GetElement()->ptr_employee_salary->GetKey();
    int grade = employee_node->GetElement()->ptr_employee_company_salary->GetElement()->grade;
    RemoveEmployee_C(EmployeeID);
    AddEmployee_C(EmployeeID, NewCompanyID, salary, grade);
    //need to add try/catch
    //make sure it doesnt cause any problem for the DS

    return SUCCESS;
}

StatusType CompaniesManager::AcquireCompany_C(int AcquirerID, int TargetID, double Factor){

    if (AcquirerID <= 0 || TargetID <= 0 || TargetID == AcquirerID || Factor<1 || TargetID==AcquirerID)
    {
        return INVALID_INPUT;
    }

    //Find the acquirer company
    Node<Company>* CompanyAcquirer_node= COMPANIES->FindNode(COMPANIES->GetRoot(),AcquirerID);
    if(CompanyAcquirer_node == nullptr)
    {
        return FAILURE;
    }

    //Find the target company
    Node<Company>* CompanyTarget_node= COMPANIES->FindNode(COMPANIES->GetRoot(),TargetID);
    if(CompanyTarget_node == nullptr)
    {
        return FAILURE;
    }

    //Check if the value is 10 times bigger
    if (10*CompanyTarget_node->GetElement()->value > CompanyAcquirer_node->GetElement()->value) {
        return FAILURE;
    }

    //Get the infos
    int num_employees_company_acquirer= CompanyAcquirer_node->GetElement()->num_of_employees;
    int value_company_acquirer= CompanyAcquirer_node->GetElement()->value;
    Node<Employee_in_company>* highest_company_acquirer = CompanyAcquirer_node->GetElement()->em_with_highest_salary;

    int num_players_company_target= CompanyTarget_node->GetElement()->num_of_employees;
    int value_company_target= CompanyTarget_node->GetElement()->value;
    Node<Employee_in_company>* highest_company_target = CompanyTarget_node->GetElement()->em_with_highest_salary;

    //new value of the company
    int new_value =  (value_company_acquirer+value_company_target)*Factor;
    CompanyAcquirer_node->GetElement()->value = new_value;

    //there arent any employees so delete the target company and finish
    if(num_employees_company_acquirer==0 && num_players_company_target==0)
    {
        delete CompanyTarget_node->GetElement()->tree_of_employees_in_company;
        delete CompanyTarget_node->GetElement()->tree_of_employees_in_company_id;
        COMPANIES->RemoveNode(TargetID);
        return SUCCESS;
    }

    //there are players at least in one of the groups
    Node<Employee_in_company >* highest_employee;

    if (num_players_company_target==0) //there's no employee in the target company so we can delete it
    {
        delete CompanyTarget_node->GetElement()->tree_of_employees_in_company;
        delete CompanyTarget_node->GetElement()->tree_of_employees_in_company_id;
        COMPANIES->RemoveNode(TargetID);
        return SUCCESS;
    }

        //there's no player in the acquirer company so we just transfer everything from the target company and finish
    else if(num_employees_company_acquirer==0)
    {
        //Add the acquirer node in the COMPANY_NOT_EMPTY
        Company_not_empty element_company_not_empty = new company_not_empty_t;
        element_company_not_empty->company = CompanyAcquirer_node;
        COMPANY_NOT_EMPTY->InsertNode(AcquirerID, element_company_not_empty, nullptr);
        this->num_of_companies_not_empty += 1;

        //Acquirer Node take the infos of Target Node and its tree
        CompanyAcquirer_node->GetElement()->num_of_employees=num_players_company_target;
        CompanyAcquirer_node->GetElement()->em_with_highest_salary = highest_company_target;
        delete CompanyAcquirer_node->GetElement()->tree_of_employees_in_company;
        delete CompanyAcquirer_node->GetElement()->tree_of_employees_in_company_id;

        CompanyAcquirer_node->GetElement()->tree_of_employees_in_company= CompanyTarget_node->GetElement()->tree_of_employees_in_company;
        CompanyAcquirer_node->GetElement()->tree_of_employees_in_company_id= CompanyTarget_node->GetElement()->tree_of_employees_in_company_id;

        UpdateCompanyAndHeight(CompanyAcquirer_node->GetElement()->tree_of_employees_in_company->GetRoot(), CompanyAcquirer_node);
        UpdateHeight(CompanyAcquirer_node->GetElement()->tree_of_employees_in_company_id->GetRoot());

        if (this->Highest_earner_in_DS == CompanyTarget_node)
            this->Highest_earner_in_DS= CompanyAcquirer_node;

        //Remove the TargetCompany from the two trees because he had employees
        this->COMPANY_NOT_EMPTY->RemoveNode(TargetID);
        this->num_of_companies_not_empty -= 1;
        COMPANIES->RemoveNode(TargetID);

        return SUCCESS;
    }

    //The two groups have players
    if  (highest_company_acquirer->GetKey() > highest_company_target->GetKey())
    {
        highest_employee=highest_company_acquirer;
    }

    else if (highest_company_acquirer->GetKey() == highest_company_target->GetKey())
    {
        if (highest_company_target->GetElement()->EmployeeID > highest_company_acquirer->GetElement()->EmployeeID)
            highest_employee=highest_company_acquirer;
        else
            highest_employee=highest_company_target;
    }

    else if(highest_company_acquirer->GetKey() < highest_company_target->GetKey()) {
        highest_employee = highest_company_target;
    }


    //Create 2 arrays with all the employees in order salary!!!
    Node<Employee_in_company> **array1 = (Node<Employee_in_company>**) malloc(sizeof(Node<Company>)*(num_employees_company_acquirer));
    CompanyInorderArray(CompanyAcquirer_node->GetElement()->tree_of_employees_in_company->GetRoot(),array1, 0);

    Node<Employee_in_company> **array2 = (Node<Employee_in_company>**) malloc(sizeof(Node<Company>)*(num_players_company_target));
    CompanyInorderArray(CompanyTarget_node->GetElement()->tree_of_employees_in_company->GetRoot(),array2, 0);

    //Merge the arrays
    Node<Employee_in_company> **array_players =
            (Node<Employee_in_company>**) malloc(sizeof(Node<Company>)*(num_players_company_target+num_employees_company_acquirer));

    int index1=0;
    int index2=0;
    int i=0;
    for (; ; i++)
    {
        if (index1>=num_employees_company_acquirer || index2>=num_players_company_target)
            break;

        if (CompareEmployees(array1[index1], array2[index2])==-1)
        {
            array_players[i]=array1[index1];
            index1++;
        }

        else
        {
            array_players[i]=array2[index2];
            index2++;
        }
    }

    if(index1>=num_employees_company_acquirer)
    {
        for (; index2<num_players_company_target; index2++)
        {
            array_players[i]=array2[index2];
            i++;
        }
    }

    else if(index2>=num_players_company_target)
    {
        for (; index1<num_employees_company_acquirer; index1++)
        {
            array_players[i]=array1[index1];
            i++;
        }
    }

    //arrays are merged! Create a new tree empty
    int size = num_players_company_target+num_employees_company_acquirer;
    Node<Employee_in_company>* root_of_new_tree;
    double h = log2(2 * size + 1);
    int h_full = (int) h ;
    if(h_full == h)
        root_of_new_tree = this->COMPANIES->GetRoot()->GetElement()->tree_of_employees_in_company->GetRoot()->BuildAvlSubtree(h_full-1);
    else
        root_of_new_tree = this->COMPANIES->GetRoot()->GetElement()->tree_of_employees_in_company->GetRoot()->BuildAvlSubtree(h_full);

    Avl_tree<Employee_in_company>* new_tree = new Avl_tree<Employee_in_company>(root_of_new_tree);
    UpdateFather(new_tree->GetRoot());
    if(h_full == h) {
        i = pow(2, h_full - 1) - size;
        new_tree->ReverseInorder(root_of_new_tree, &i);
    }
    else {
        i = pow(2, h_full) - 1 - size;
        new_tree->ReverseInorder(root_of_new_tree, &i);
    }

    new_tree->SetRoot(root_of_new_tree);
    new_tree->Inorder(new_tree->Get_smallest_node(), array_players, size);


    //****************************************************************
    //Create 2 arrays with all the employees ID!!!!
    Node<Employee> **array_id1 = (Node<Employee>**) malloc(sizeof(Node<Company>)*(num_employees_company_acquirer));
    CompanyInorderArrayID(CompanyAcquirer_node->GetElement()->tree_of_employees_in_company_id->GetRoot(),array_id1, 0);

    Node<Employee> **array_id2 = (Node<Employee>**) malloc(sizeof(Node<Company>)*(num_players_company_target));
    CompanyInorderArrayID(CompanyTarget_node->GetElement()->tree_of_employees_in_company_id->GetRoot(),array_id2, 0);

    //Merge the arrays
    Node<Employee> **array_employees_id =
            (Node<Employee>**) malloc(sizeof(Node<Company>)*(num_players_company_target+num_employees_company_acquirer));

    int index_id1=0;
    int index_id2=0;
    i=0;
    for (; ; i++)
    {
        if (index_id1>=num_employees_company_acquirer || index_id2>=num_players_company_target)
            break;

        if (array_id1[index_id1]->GetKey() < array_id2[index_id2]->GetKey())
        {
            array_employees_id[i]=array_id1[index_id1];
            index_id1++;
        }

        else
        {
            array_employees_id[i]=array_id2[index_id2];
            index_id2++;
        }
    }

    if(index_id1>=num_employees_company_acquirer)
    {
        for (; index_id2<num_players_company_target; index_id2++)
        {
            array_employees_id[i]=array_id2[index_id2];
            i++;
        }
    }

    else if(index_id2>=num_players_company_target)
    {
        for (; index_id1<num_employees_company_acquirer; index_id1++)
        {
            array_employees_id[i]=array_id1[index_id1];
            i++;
        }
    }

    //arrays are merged! Create a new tree empty
    int size_id = num_players_company_target+num_employees_company_acquirer;
    Node<Employee>* root_of_new_tree_id;
    double h_id = log2(2 * size + 1);
    int h_full_id = (int) h ;
    if(h_full == h)
        root_of_new_tree_id = this->COMPANIES->GetRoot()->GetElement()->tree_of_employees_in_company_id->GetRoot()->BuildAvlSubtree(h_full_id-1);
    else
        root_of_new_tree_id = this->COMPANIES->GetRoot()->GetElement()->tree_of_employees_in_company_id->GetRoot()->BuildAvlSubtree(h_full_id);

    Avl_tree<Employee>* new_tree_id = new Avl_tree<Employee>(root_of_new_tree_id);
    UpdateFatherID(new_tree_id->GetRoot());
    if(h_full_id == h_id) {
        int k = pow(2, h_full_id - 1) - size_id;
        new_tree_id->ReverseInorder(root_of_new_tree_id, &k);
    }
    else {
        int k = pow(2, h_full_id) - 1 - size_id;
        new_tree_id->ReverseInorder(root_of_new_tree_id, &k);
    }

    new_tree_id->SetRoot(root_of_new_tree_id);
    new_tree_id->Inorder(new_tree_id->Get_smallest_node(), array_employees_id, size_id);

    //*****************************************************

    //Update highest
    if (this->Highest_earner_in_DS == CompanyTarget_node)
        this->Highest_earner_in_DS= CompanyAcquirer_node;

    delete CompanyTarget_node->GetElement()->tree_of_employees_in_company;
    delete CompanyAcquirer_node->GetElement()->tree_of_employees_in_company;
    delete CompanyTarget_node->GetElement()->tree_of_employees_in_company_id;
    delete CompanyAcquirer_node->GetElement()->tree_of_employees_in_company_id;

    CompanyAcquirer_node->GetElement()->tree_of_employees_in_company = new_tree;
    CompanyAcquirer_node->GetElement()->tree_of_employees_in_company_id = new_tree_id;
    CompanyAcquirer_node->GetElement()->em_with_highest_salary= highest_employee;
    CompanyAcquirer_node->GetElement()->num_of_employees = size;
    UpdateCompanyAndHeight(new_tree->GetRoot(), CompanyAcquirer_node);
    UpdateFather(new_tree->GetRoot());
    UpdateHeight(new_tree_id->GetRoot());
    UpdateFatherID(new_tree_id->GetRoot());

    COMPANIES->RemoveNode(TargetID);
    if (num_players_company_target!=0)
    {
        COMPANY_NOT_EMPTY->RemoveNode(TargetID);
        this->num_of_companies_not_empty -= 1;
    }

    free(array1);
    free(array2);
    free(array_players);
    free(array_id1);
    free(array_id2);
    free(array_employees_id);

    return SUCCESS;
}

StatusType CompaniesManager::GetHighestEarner_C(int CompanyID, int *EmployeeID) {

    if (CompanyID == 0 || EmployeeID == nullptr)
        return INVALID_INPUT;


    if (CompanyID < 0) {
        Node<Company> *company_with_highest_earner = this->Highest_earner_in_DS;
        //no employee in the company
        if (company_with_highest_earner == nullptr) {
            return FAILURE;
        }

        Company company_element_highest = (Company) company_with_highest_earner->GetElement();
        Employee_in_company element_employee_highest = (Employee_in_company) company_element_highest->em_with_highest_salary->GetElement();
        int Id_to_return = element_employee_highest->EmployeeID;
        *EmployeeID = Id_to_return;
        return SUCCESS;
    }

    //Company ID is >=0
    Node<Company> *company_to_search = COMPANIES->FindNode(COMPANIES->GetRoot(), CompanyID);

    if (company_to_search == nullptr) //group does not exist
    {
        return FAILURE;
    }

    Company element_company = (Company) company_to_search->GetElement();
    if (element_company->em_with_highest_salary == nullptr) //There are no employees
    {
        return FAILURE;
    }

    int PlayerId_value = element_company->em_with_highest_salary->GetElement()->EmployeeID;

    *EmployeeID = PlayerId_value;

    return SUCCESS;
}

StatusType CompaniesManager::GetAllEmployeesBySalary_C(int CompanyID, int **Employees, int *NumOfEmployees) {

    if(Employees == nullptr || NumOfEmployees == nullptr || CompanyID == 0)
    {
        return INVALID_INPUT;
    }

    if(CompanyID > 0)
    {
        Node<Company>* wanted_group = COMPANIES->FindNode(COMPANIES->GetRoot(), CompanyID);

        if(wanted_group == nullptr)
        {
            return FAILURE;
        }

        if(wanted_group->GetElement()->num_of_employees == 0)
        {
//            int* new_arr_players = (int*) malloc(sizeof (int) * 1);
//            *Employees = new_arr_players;
//            *NumOfEmployees = 0;
//            return SUCCESS;
            return FAILURE;
        }

        *NumOfEmployees = wanted_group->GetElement()->num_of_employees;

        int* arr_players = (int*)malloc(sizeof(int) * (*NumOfEmployees));
        //null arg

        wanted_group->GetElement()->tree_of_employees_in_company->InorderVisit(wanted_group->GetElement()->tree_of_employees_in_company->GetRoot(), arr_players, 0);

        int* new_arr_players = (int*)malloc(sizeof(int) * (*NumOfEmployees));

        for (int k = (*NumOfEmployees) - 1, j = 0; j < (*NumOfEmployees) && k >= 0; j++ , k--)
        {
            new_arr_players[j] = arr_players[k];
        }

        free(arr_players);

        *Employees = new_arr_players;

        return SUCCESS;
    }


    else if(CompanyID < 0)
    {
        if(EMPLOYEES_SALARY->GetRoot() == nullptr)
        {
//            *Employees = nullptr;
//            *NumOfEmployees = 0;
//            return SUCCESS;
            return FAILURE;
        }

        *NumOfEmployees = EMPLOYEES_SALARY->CountNodesOfTree(EMPLOYEES_SALARY->GetRoot());

        int* arr_players = (int*)malloc(sizeof(int) * (*NumOfEmployees));
        //null arg

        EMPLOYEES_SALARY->InorderVisit(EMPLOYEES_SALARY->GetRoot(), arr_players, 0);

        int* new_arr_players = (int*)malloc(sizeof(int) * (*NumOfEmployees));

        for (int k = (*NumOfEmployees) - 1, j = 0; j < (*NumOfEmployees) && k >= 0; j++ , k--)
        {
            new_arr_players[j] = arr_players[k];
        }

        free(arr_players);

        *Employees = new_arr_players;

        return SUCCESS;
    }

    return SUCCESS;

}

StatusType CompaniesManager::GetHighestEarnerInEachCompany_C(int NumOfCompanies, int **Employees) {

    if (NumOfCompanies < 1 || Employees== nullptr)
    {
        return INVALID_INPUT;
    }

    if (COMPANIES->GetRoot()== nullptr) //There are no group
    {
        return SUCCESS;
    }

    int count = this->num_of_companies_not_empty;

    if(NumOfCompanies > count)
    {
        return FAILURE;
    }

    *Employees = (int*)malloc(sizeof(int)*NumOfCompanies);

    if (Employees== nullptr)
        return ALLOCATION_ERROR;

    int res= CompanyInorder(COMPANY_NOT_EMPTY->Get_smallest_node(), Employees, NumOfCompanies);

    if (res==0)
    {
        return FAILURE;
    }

    return SUCCESS;
}

StatusType CompaniesManager::GetNumEmployeesMatching_C(int CompanyID, int MinEmployeeID, int MaxEmployeeId,
                                                       int MinSalary, int MinGrade, int *TotalNumOfEmployees, int *NumOfEmployees){

    if (CompanyID==0 || MinEmployeeID<0 || MaxEmployeeId < 0 || MinSalary <0 || MinGrade<0 || NumOfEmployees== nullptr)
    {
        return INVALID_INPUT;
    }

    if (MaxEmployeeId<MinEmployeeID)
    {
        return INVALID_INPUT;
    }

    int numEmployeesID=0;
    int numEmployeesSalaryGrade=0;

    if (CompanyID<0)
    {
        //Theres no employees
        if (EMPLOYEES_ID->GetRoot()== nullptr)
            return FAILURE;

        //Theres an employee: Search for "MinEmployeeID", if doesnt exist add it
        Node<Employee> *Employee_to_count = EMPLOYEES_ID->FindNode(EMPLOYEES_ID->GetRoot(), MinEmployeeID);

        bool MinWasAdded=false;

        if(MinEmployeeID<=0){
            Employee_to_count = EMPLOYEES_ID->Get_smallest_node();
        }

        else if (Employee_to_count == nullptr)
        {
            MinWasAdded=true;
            Employee employee;
            try {
                employee = new employee_t;
            }
            catch (std::bad_alloc &) {
                return ALLOCATION_ERROR;
            }
            employee->ptr_employee_company_salary= nullptr;
            employee->ptr_employee_salary= nullptr;
            AVLResults res = EMPLOYEES_ID->InsertNode(MinEmployeeID,employee, nullptr);
            Employee_to_count = EMPLOYEES_ID->FindNode(EMPLOYEES_ID->GetRoot(), MinEmployeeID);
        }

        while (Employee_to_count->GetKey()<=MaxEmployeeId)
        {
            Node<Employee_in_company>* employee_infos = Employee_to_count->GetElement()->ptr_employee_company_salary;
            if (employee_infos== nullptr){      //in case the minID was added we dont count it
                Employee_to_count= Employee_to_count->Get_Following_node();
                if (Employee_to_count== nullptr)
                    break;
                continue;
            }

            numEmployeesID++;
            if (employee_infos->GetElement()->grade>=MinGrade && employee_infos->GetKey() >=MinSalary)
                numEmployeesSalaryGrade++;

            Employee_to_count = Employee_to_count->Get_Following_node();
            if (Employee_to_count== nullptr) //No more nodes
                break;
        }

        if (MinWasAdded==true) //if it was added remove it
        {
            EMPLOYEES_ID->RemoveNode(MinEmployeeID);
        }

        *TotalNumOfEmployees = numEmployeesID;
        *NumOfEmployees= numEmployeesSalaryGrade;

        return SUCCESS;
    }


    if (CompanyID>0)
    {
        Node<Company> *company = COMPANIES->FindNode(COMPANIES->GetRoot(), CompanyID);
        //Theres no company
        if (company== nullptr)
            return FAILURE;

        //Theres no employees
        if (company->GetElement()->num_of_employees==0)
            return FAILURE;

        Avl_tree<Employee>* tree_company = company->GetElement()->tree_of_employees_in_company_id;

        //Theres an employee: Search for "MinEmployeeID", if doesnt exist add it
        Node<Employee> *Employee_to_count = tree_company->FindNode(tree_company->GetRoot(), MinEmployeeID);
        bool MinWasAdded=false;

        if(MinEmployeeID == 0){
            Employee_to_count = tree_company->Get_smallest_node();
        }

        else if (Employee_to_count== nullptr)
        {
            //Add it
            MinWasAdded=true;
            Employee employee;
            try {
                employee = new employee_t;
            }
            catch (std::bad_alloc &) {
                return ALLOCATION_ERROR;
            }
            employee->ptr_employee_company_salary = nullptr;
            employee->ptr_employee_salary = nullptr;
            tree_company->InsertNode(MinEmployeeID,employee, nullptr);
            Employee_to_count = tree_company->FindNode(tree_company->GetRoot(), MinEmployeeID);
        }

        //Inorder to count all the employees<MaxEmployeeID and those who have salary/grade needed

        while (Employee_to_count->GetKey()<=MaxEmployeeId)
        {
            Node<Employee_in_company>* employee_infos = Employee_to_count->GetElement()->ptr_employee_company_salary;
            if (employee_infos== nullptr){      //in case the minID was added we dont count it
                Employee_to_count= Employee_to_count->Get_Following_node();
                if (Employee_to_count== nullptr)
                    break;
                continue;
            }

            numEmployeesID++;
            if (employee_infos->GetElement()->grade>=MinGrade && employee_infos->GetKey()>=MinSalary)
                numEmployeesSalaryGrade++;

            Employee_to_count= Employee_to_count->Get_Following_node();
            if (Employee_to_count== nullptr) //No more nodes
                break;
        }

        if (MinWasAdded==true) //if it was added remove it
        {
            tree_company->RemoveNode(MinEmployeeID);
        }

        *TotalNumOfEmployees = numEmployeesID;
        *NumOfEmployees= numEmployeesSalaryGrade;

        return SUCCESS;
    }
    return SUCCESS;
}


void CompaniesManager::Quit_C() {
    RemoveInorderTree(COMPANIES->GetRoot());
    this->EMPLOYEES_SALARY->AuxDistructorTree(EMPLOYEES_SALARY->GetRoot());
    this->COMPANIES->AuxDistructorTree(COMPANIES->GetRoot());
    this->EMPLOYEES_ID->AuxDistructorTree(this->EMPLOYEES_ID->GetRoot());
    this->COMPANY_NOT_EMPTY->AuxDistructorTree(this->COMPANY_NOT_EMPTY->GetRoot());
}



