SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";
CREATE DATABASE IF NOT EXISTS `chatroom` DEFAULT CHARACTER SET utf8 COLLATE utf8_general_ci;
USE chatroom;

CREATE TABLE user (
      `id` int(11) NOT NULL,
      `name` varchar(10) NOT NULL,
      `passwd` varchar(33) NOT NULL,
      `online` int(11) NOT NULL,
      `sock_fd` int(11) NOT NULL

) ENGINE=InnoDB DEFAULT CHARSET=utf8;


CREATE TABLE `friends` (
      `id1` int(11) NOT NULL,
      `id2` int(11) NOT NULL
);

CREATE TABLE `chat_fri` (
      `id1` int(11) NOT NULL,
      `id2` int(11) NOT NULL,
      `mes` varchar(1000) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `groups` (
      `id` int(11) NOT NULL, 
      `account` int(11) NOT NULL,
      `group_name` varchar(20) NOT NULL

) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `g_member` (
      `group_id` int(11) NOT NULL,
      `group_member` int(11) NOT NULL,
      `member_flag` int(11) NOT NULL

) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `chat_group` (
      `group_id` int(11) NOT NULL,
      `group_member` int(11) NOT NULL,
      `mes` varchar(300) NOT NULL

) ENGINE=InnoDB DEFAULT CHARSET=utf8;



ALTER TABLE `user`
  ADD PRIMARY KEY (`id`);

ALTER TABLE `friends`
  ADD PRIMARY KEY (`id1`,`id2`);

ALTER TABLE `groups`
  ADD PRIMARY KEY (`id`);

ALTER TABLE `g_member`
  ADD PRIMARY KEY (`group_id`,`group_member`);


ALTER TABLE `user`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;

ALTER TABLE `groups`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=2;
COMMIT;
