SELECT gender,count(e.emp_no) FROM employees e
JOIN dept_emp de ON de.emp_no=e.emp_no
JOIN departments d ON d.dept_no=de.dept_no
WHERE d.dept_name='Sales'
GROUP BY gender;