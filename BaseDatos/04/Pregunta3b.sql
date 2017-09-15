SELECT gender,count(e.emp_no) FROM employees e
JOIN dept_emp de ON de.emp_no=e.emp_no
JOIN departments d ON d.dept_no=de.dept_no
WHERE d.dept_name='Sales' 
AND (de.from_date<='1992-12-31' AND de.to_date>='1992-01-01')
GROUP BY gender;