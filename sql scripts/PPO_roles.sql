--����

--�������� guest
REASSIGN OWNED BY guest TO postgres;
DROP OWNED BY guest;
drop role guest;
--�������� canvas_user
REASSIGN OWNED BY canvas_user TO postgres;
DROP OWNED BY canvas_user;
drop role canvas_user;
--�������� moderator
REASSIGN OWNED BY moderator TO postgres;
DROP OWNED BY moderator;
drop role moderator;


/*
--�������� ���� canvas_user
revoke pg_read_all_data from guest;
revoke ALL on ppo.users FROM guest
revoke ALL on ppo.users_id_seq FROM guest
--�������� ���� canvas_user
revoke pg_read_all_data FROM canvas_user;
REVOKE ALL ON ppo.canvas FROM canvas_user;
REVOKE ALL ON ppo.canvas_id_seq FROM canvas_user;
REVOKE ALL ON ppo.users FROM canvas_user
--�������� moderator
revoke pg_read_all_data FROM moderator;
REVOKE ALL ON ppo.users FROM moderator;
*/

--�������� guest
CREATE USER guest password 'guest';
--���������� ���� guest
grant pg_read_all_data to guest;
grant insert on ppo.users to guest;
grant update on ppo.users_id_seq to guest;

--�������� canvas_user
CREATE USER canvas_user password 'canvas_user';
--���������� ���� canvas_user
grant pg_read_all_data to canvas_user;
grant select, insert, update, delete on ppo.canvas to canvas_user;
grant update on ppo.canvas_id_seq to canvas_user;
grant delete on ppo.users to canvas_user;
grant select, insert, update, delete on ppo.params to canvas_user;

--�������� moderator
CREATE USER moderator password 'moderator';
--���������� ���� moderator
grant pg_read_all_data to moderator;
grant select, update, delete on ppo.users to moderator;


--SELECT rolname FROM pg_roles;
--SELECT current_user, session_user;