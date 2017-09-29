
select * from departments d
LEFT JOIN dept_manager m on d.dept_no=m.dept_no
where m.dept_no is NULL