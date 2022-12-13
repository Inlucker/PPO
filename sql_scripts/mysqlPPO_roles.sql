#Роли
SELECT * FROM mysql.user;
#Удаление guest
drop role 'guest'@'localhost';
#Удаление canvas_user
drop role 'canvas_user'@'localhost';
#Удаление moderator
drop role 'moderator'@'localhost';


/*
#Удаление прав canvas_user
revoke pg_read_all_data from guest;
revoke ALL on PPO.Users FROM guest
revoke ALL on PPO.Users_id_seq FROM guest
#Удаление прав canvas_user
revoke pg_read_all_data FROM canvas_user;
REVOKE ALL ON PPO.canvas FROM canvas_user;
REVOKE ALL ON PPO.canvas_id_seq FROM canvas_user;
REVOKE ALL ON PPO.Users FROM canvas_user
#Удаление moderator
revoke pg_read_all_data FROM moderator;
REVOKE ALL ON PPO.Users FROM moderator;
*/

#Создание guest
CREATE USER 'guest'@'localhost' IDENTIFIED BY 'guest';
#Добавление прав guest
grant insert on PPO.Users to 'guest'@'localhost';

GRANT 'root' TO 'guest'@'localhost';
GRANT SELECT ON PPO.* TO 'guest'@'localhost';
REVOKE SELECT ON PPO.* FROM 'guest'@'localhost';
FLUSH PRIVILEGES;


#TESTS
CREATE SCHEMA test_DB;
CREATE USER 'test_user'@'localhost' IDENTIFIED BY 'secret';
GRANT SELECT ON `test_db`.* TO 'test_user'@'localhost';
FLUSH PRIVILEGES;

#NOT YET
GRANT ALL ON PPO.Users TO 'guest'@'localhost';

select * from  PPO.Users;

grant pg_read_all_data to guest;
grant insert on PPO.Users to guest;
grant update on PPO.Users_id_seq to guest;

SHOW GRANTS FOR 'guest'@'localhost'

#Создание canvas_user
CREATE USER 'canvas_user'@'localhost' IDENTIFIED BY 'canvas_user';
#Добавление прав canvas_user
grant pg_read_all_data to canvas_user;
grant select, insert, update, delete on PPO.canvas to canvas_user;
grant update on PPO.canvas_id_seq to canvas_user;
grant delete on PPO.Users to canvas_user;

#Создание moderator
CREATE USER 'moderator'@'localhost' IDENTIFIED BY 'moderator';
#Добавление прав moderator
grant pg_read_all_data to moderator;
grant select, update, delete on PPO.Users to moderator;


#SELECT rolname FROM pg_roles;
#SELECT current_user, session_user;