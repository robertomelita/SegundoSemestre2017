use employees;
select * from employees e
LEFT JOIN salaries s on e.emp_no=s.emp_no
WHERE s.emp_no is NULL
UNION
SELECT * from employees e
LEFT JOIN titles t on e.emp_no = t.emp_no
WHERE t.emp_no is NULL;