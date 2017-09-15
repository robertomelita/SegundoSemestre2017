select first_name, last_name from employees e
join dept_emp de on e.emp_no=de.emp_no
join departments d on d.dept_no=de.dept_no
WHERE de.from_date>='1990-01-01' AND dept_name='Sales';