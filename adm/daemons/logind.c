// logind.c
//  By  Spiderii@ty Ϊ����Ϸ���У��޸Ķ��
#include <ansi.h>
#include <command.h>
#include <login.h>
#include <mudlib.h>

inherit F_DBASE;

int wiz_lock_level = WIZ_LOCK_LEVEL;
int ppls = 0;
int maxusers = MAX_USERS;
string welcome_msg;

private void get_id(string, object);
private void confirm_id(string, object);
object make_body(object);
private void init_new_player(object);
varargs void enter_world(object, object, int);
varargs void reconnect(object, object, int);
object find_body(string);
int check_legal_id(string);
int check_legal_name(object, string);
private void get_email(string, object, mapping);

private void random_gift(mapping my, int select)
{
	int i = 10, j;
	int tmpstr, tmpint, tmpcon, tmpdex;

	tmpstr = tmpint = tmpcon = tmpdex = 10;

	switch (select) {
		case 1: tmpstr = i = my["str"]; break;
		case 2: tmpint = i = my["int"]; break;
		case 3: tmpcon = i = my["con"]; break;
		case 4: tmpdex = i = my["dex"];
	}
	i = 50 - i;
	while (i--) {
		j = random(4);
		if (j == select - 1) i++;
		else switch (j) {
			case 0: if (tmpstr < 30) tmpstr++;
				else i++;
				break;
			case 1: if (tmpint < 30) tmpint++;
				else i++;
				break;
			case 2: if (tmpcon < 30) tmpcon++;
				else i++;
				break;
			case 3: if (tmpdex < 30) tmpdex++;
				else i++;
		}
	}
	my["str"] = tmpstr;
	my["int"] = tmpint;
	my["con"] = tmpcon;
	my["dex"] = tmpdex;
	// next 3 are randomly selected
	my["kar"] = 10 + random(21);
	my["per"] = 10 + random(21);
	my["pur"] = 10 + random(21);
}

void create()
{
	seteuid(getuid());
	set("channel_id", "���߾���");
	set("md5", crypt("ShuJian", "$1") != crypt("ShuJian", "$1$"));
	if (file_size("/log/ppls") > 0)
		sscanf(read_file("/log/ppls"), "%d", ppls);
	if (file_size(WELCOME) > 0)
		welcome_msg = read_file(WELCOME);
	else welcome_msg = sprintf("\n%76|s\n\n", "��ӭ����"HIW" "CHINESE_MUD_NAME" "NOR"������Ϸ");
            welcome_msg += sprintf("\n%75|s\n\n", HIW"��ϷQQȺ[" QQ_QUN_NUMBER "]"NOR);
	if (file_size("/adm/etc/maxusers") > 0)
		sscanf("\n"+read_file("/adm/etc/maxusers"), "%*s\n" INTERMUD_MUD_NAME " %d\n", maxusers);
	welcome_msg += "��վĿǰ�������ޣ�" HIY + chinese_number(maxusers) + NOR "\n"
		+ "��վ������뷽ʽ��"HIY+(query("md5")?
		"MD5 ֧�����ⳤ�ȵ�����":"DES ֧�� 8 ���ַ����ȵ�����")+NOR+"\n";
}

int remove()
{
	write_file("/log/ppls", sprintf("%d", ppls), 1);
	return 1;
}

void logon(object ob)
{
	object *usr;
	int login_cnt = 0;
	string ip = query_ip_number(ob);

	if (++ppls % 100 == 0) remove();
// ��ֹ�ж��������� KMUD �ȹ��ߵ���
	usr = filter_array(children(LOGIN_OB), (: interactive :));
	foreach (object item in usr)
		login_cnt += query_ip_number(item) == ip;
	if (login_cnt > 2) {
		destruct(ob);
		return;
	}
// Add by Yu Jue 1997.8.6
        write("\nBest view with 800 * 600 or better, Fixedsys font.\nAre you using BIG5 font(Y/N)? ");
	input_to("gb_big5", ob);
}

void gb_big5(string arg, object ob)
{
	if (lower_case(arg)[0] == 'y')
		ob->set_temp("big5", 1);
	if (BAN_D->is_banned(query_ip_number(ob))) {
		write("�Բ������ĵ�ַ��" + MUD_NAME + "���ܻ�ӭ��\n");
		destruct(ob);
		return;
	}
	write(sprintf("\n%76|s\n%76|s\n%s", MUD_NAME, "- " __VERSION__ " -", welcome_msg));
	write("��վ�ܹ������˴Σ�" HIY + chinese_number(ppls) + NOR "\n");
	UPTIME_CMD->main(1);
	"/cmds/usr/mudlist"->main(ob, "all");

	write("����Ӣ������(ID)�ǣ�");
	input_to((: get_id :), ob);
}

private void get_id(string arg, object ob)
{
	int i,mysql;
	object ppl, *usr;
	string ip = query_ip_number(ob);
	mixed rows;

	arg = lower_case(arg);
	if (!check_legal_id(arg)) {
		write("����Ӣ������(ID)�ǣ�");
		input_to((: get_id :), ob);
		return;
	}

/* 
  if (!__DIR__"sited"->is_valid(arg, ip)) {
		log_file("SITE", sprintf("%-9s�� %-16s���ܾ�(%s)\n", arg, ip, ctime(time())[4..18]));
		write("�Բ������Ӣ�����ֲ��ܴӵ�ǰ��ַ��¼��\n");
		write("����Ӣ������(ID)�ǣ�");
		input_to("get_id", ob);
		return;
	}
*/
	if ("/cmds/usr/blacklist"->is_black(arg)) {
		write("���ź������Ǻ������е������ȴ����������\n");
		destruct(ob);
		return;
	}

	if (ob->set("id", arg) != arg) {
		write("Failed setting user name.\n");
		destruct(ob);
		return;
	}

	ppl = find_body(arg);
	if (!ppl && !wiz_level(arg)) {
		usr = filter_array(users(), (: environment :));
		if (sizeof(usr) >= maxusers) {
		// Only allow reconnect an player in MUD when MAX_USERS exceeded.
			write("�Բ���Ŀǰ" + MUD_NAME + "������Ѿ�̫���ˣ������������\n");
			destruct(ob);
			return;
		}
		// check multilogin Yu Jue 1999-03-23
//hxsdΪ�����޸ģ�ɾ��
		//���ﲻ������  by renlai
		
		/*
		if (__DIR__"sited"->is_multi(arg, ip,)) {
			destruct(ob);
			return;
		}
		*/
	}

	// add by snowman@SJ 16/02/2000, wiz_lock���½�����Ҳ����login.
	if (wiz_level(arg) < wiz_lock_level) {
		write("�Բ���" + MUD_NAME + "Ŀǰ������ʦ�ȼ� "+wiz_lock_level+" ���ϵ��˲������ߡ�\n");
		destruct(ob);
		return;
	}

	if (arg == "guest") {
		// If guest, let them create the character.
		ob->set("password", "SJGUEST");
		write("�����������֣�");
		input_to("get_name", ob);
		return;
	}

	if (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0) {
		if (ob->restore()) {
			write("Ӣ�� ID �Ѿ����ڣ��������������ֱ�ӻس�����ѡ�� ID��\n");
			write("����������������ʶ������(passwd)��");
			input_to("get_passwd", 1, ob);
			return;
		}
		write("�������ﵵ������һЩ���⣬������ guest ��¼֪ͨ��ʦ������\n");
		destruct(ob);
		return;
	}

	// ��ֹ��������ͬһ id
	usr = filter_array(children(LOGIN_OB), (: interactive :));
	i = sizeof(usr);
	while (i--)
		if (usr[i] != ob && usr[i]->query("id") == arg)
			break;
	if (i >= 0) {
		ob->delete("id");
		write("���������Ҳ��ʹ����� ID ������������������롣\n");
		write("����Ӣ������(ID)�ǣ�");
		input_to((: get_id :), ob);
		return;
	}
	//Add by bbb 2000.9.18
//hxsd�޸�
/*
	mysql = db_connect("localhost","bbs","root");
	if (intp(mysql)) {
		rows = db_exec(mysql, "select U_Username from Users where U_Username=\""+ob->query("id")+"\"");
		db_close(mysql);
		if (rows) {
			write("��� ID ���齣�����Ѿ���ʹ���ˣ����������롣\n");
			write("����Ӣ������(ID)�ǣ�");
			input_to((: get_id :), ob);
			return;
		}
	}
	// Add by Yu Jue 1998.8.24
*/
	write("ʹ�� " + arg + " ������ֽ����ڴ˴���һ���µ������ȷ����(y/N)��");
	input_to("confirm_id", ob);
}

private void get_passwd(string pass, object ob)
{
	string my_pass, new_pass;
	object user;
	int mysql;
	mixed rows;
	string ip_number = query_ip_number(ob);

	if (query_temp("step2/"+ip_number) >= 3) {
		write("ϵͳ��⵽�����ַ���˶�������������룬��ʱ��ֹ��¼��\n");
		destruct(ob);
		return;
	}

	if (query_temp("step1/"+ip_number) >= 3) {
		if (add_temp("step2/"+ip_number, 1)==1)	// YUJ@SJ 2001-12-11
			call_out("delete_temp", 600, "step2/"+ip_number);
		write("ϵͳ��⵽�����ַ���˶�������������룬��ʱ��ֹ��¼��\n");
		destruct(ob);
		return;
	}

	write("\n");
	if (pass == "") {
		ob->delete("id");
		write("����Ӣ������(ID)�ǣ�");
		input_to((: get_id :), ob);
		return;
	}

	my_pass = ob->query("password");
	new_pass = ob->query("newpassword");

	switch (ob->query("registered")) {
		case 1:
			if (crypt(pass, new_pass) == new_pass) {
				ob->set("registered", 2);
				ob->delete("newpassword");
				ob->save();
				log_file("maillist", ob->query("email") +" "+ ob->query("id") +" "+ ctime(time())[4..18] +"\n");
				write(BLINK HIY "\n�Ǽǳɹ�������Լ���ʹ��ԭ����������Ϸ��\n" NOR);
				break;
			}
		default:
			if (crypt(pass, my_pass) != my_pass && oldcrypt(pass, my_pass) != my_pass) {
				write("\n������������벢����ȷ�������Ƿ����������\n");
				if (add_temp("step1/"+ip_number, 1)==1)	// YUJ@SJ 2001-12-11
					call_out("delete_temp", 30, "step1/"+ip_number);
				log_file( "USAGE", sprintf("%s ���� %15s ��ĳ����ͼʹ�ã�%16s ��¼ %s\n",ctime(time())[4..18], ip_number, pass, capitalize(""+ob->query("id")) ));
				ob->add("login_fail", 1);
				ob->save();
				destruct(ob);
				return;
			}
			ob->set("password", crypt(pass, "$1$ShuJian"));
	}
//hxsd�޸�
/*
	if (ob->query("registered") == 2) {
		mysql = db_connect("localhost","bbs","root");
		if (intp(mysql)) {
			rows = db_exec(mysql, "select U_Username from Users where U_Username=\""+ob->query("id")+"\"");
			if (!rows) {
				rows = db_exec(mysql, "insert into Users set U_Username=\""
					+ob->query("id")+"\",U_Password=\""+ob->query("password")
					+"\",U_Email=\""+ob->query("email")+"\",U_Name=\""
					+ob->query("name")+"\",U_Registered=\""+time()+"\",U_RegIP=\""
					+query_ip_number(ob)+"\",Mud_Site=\""+CHINESE_MUD_NAME+"\"");
				if (intp(rows)) {
					log_file("webreg", ob->query("id") +" "+ ctime(time())[4..18]
						+" �� " +query_ip_number(ob)+" �ɹ�ע������\n");
					write(BLINK HIY "\n����ע��ɹ���������ø��ʺŵ�¼ http://www.mymud.com/ ������\n" NOR);
					ob->set("registered", 3);
					ob->save();
				}
			} else if (intp(rows)) {
				log_file("regerror", ob->query("id")+"\n");
				ob->set("registered", 4);
				ob->save();
			}
			db_close(mysql);
		}
	}
*/
	// Check if we are already playing.
	user = find_body(ob->query("id"));
	if (user) {
		if (user->query("registered") == 1) {
			//message_vision("$N�뿪������䡣\n", user);
			if (user->query_temp("link_ob")) destruct(user->query_temp("link_ob"));
			destruct(user);
		}
	}
	if (user) {
		if (!interactive(user)) {
			log_file( "USAGE", sprintf("%-19s�� %-16s����(%s)\n",
				user->query("name")+"("+capitalize(""+user->query("id"))+")",
				query_ip_number(ob), ctime(time())[4..18]));
			reconnect(ob, user);
			return;
		}
		write("����Ŀǰ������Ϸ���У�������ȡ����֮��ȷ����� Y ��������� N ��ȷ����(y/N)��");
		input_to("confirm_relogin", ob, user);
		return;
	}

	
        // ����Ƶ���˳�����¼ YUJ@SJ 2001-0530
       if (time() - ob->query("last_on") < 30 && !wiz_level(ob->query("id"))) {
		write("����ܸո��˳�������ɱ���������ϵ�¼��\n");
		destruct(ob);
		return;
        }

		
        if (objectp(user = make_body(ob))) {
		if (user->restore()) {
			log_file( "USAGE", sprintf("%-19s�� %-16s��¼(%s)\n",
				user->query("name")+"("+capitalize(""+user->query("id"))+")",
				query_ip_number(ob), ctime(time())[4..18]));
			enter_world(ob, user);
			return;
		}
		destruct(user);
	}
	write("�������´���������\n");
	confirm_id("y", ob);
}

private void confirm_relogin(string yn, object ob, object user)
{
	object old_link;

	if (!user) {
		write("��Ҫȡ���������Ѿ��˳���Ϸ�������µ�¼��\n");
		destruct(ob);
		return;
	}
	if (lower_case(yn)[0] != 'y') {
		write("�ðɣ���ӭ�´�����" + MUD_NAME + "��\n");
		destruct(ob);
		return;
	}
	tell_object(user, "\n���˴ӱ�(" + query_ip_name(ob)+ ")����ȡ���������Ƶ����\n\n");
	log_file( "USAGE", sprintf("%-19s�� %-16s����(%s)\n",
		user->query("name")+"("+capitalize(""+user->query("id"))+")",
		query_ip_number(ob), ctime(time())[4..18]));

	// Kick out the old player.
	old_link = user->query_temp("link_ob");
	if (old_link) {
		if (interactive(user)) {
			old_link->set("last_on", time());
			old_link->set("last_from", query_ip_name(user)+"("+query_ip_number(user)+")");
			old_link->save();
			ob->restore();
			exec(old_link, user);
		}
		destruct(old_link);
	}
	reconnect(ob, user);
}

private void confirm_id(string yn, object ob)
{
	if ( yn=="" ) {
		write("ʹ��������ֽ��ᴴ��һ���µ������ȷ����(y/n)��");

		input_to("confirm_id", ob);
		return;
	}
	
	
	
	
	
//----------------------------------------------------------------------------------------------------------------------------------------ע������
/*
        if (lower_case(yn)[0] == 'y') {
		ob->delete("id");

		write("\n�Բ���Ŀǰ�齣��̴վ��ʱ���������ע�ᣬ�����QQȺ88397272����ȡ�����롣\n\n");
		write("��������������Ӣ�����֣�");
		input_to((: get_id :), ob);
		return;
	}
*/
        if (lower_case(yn)[0] != 'y') {
		ob->delete("id");
		write("��������������Ӣ�����֣�");
		input_to((: get_id :), ob);
		return;
	}
	write("����ĳ�������Ҫ����ַ������ұ���������ֺ�Ӣ�Ĵ�д��ĸ��\n���趨�������룺");
	input_to("new_password", 1, ob);
}

private void new_password(string pass, object ob)
{
	int i = strlen(pass), j = 0 ,k = 0;

	write("\n");

	if (i < 5) {
		write("Ϊ�˱�֤��ȫ������ĳ�������Ҫ����ַ���\n");
		write("�������������룺");
		input_to("new_password", 1, ob);
		return;
	}

	if (!query("md5") && i > 8) {
		write("��Ϊ�� DES ���룬����ĳ������ֻ�ܰ˸��ַ���\n");
		write("�������������룺");
		input_to("new_password", 1, ob);
		return;
	}

	while (i--) {
		if (pass[i]>='0' && pass[i]<='9') j++;
		if (pass[i]>='A' && pass[i]<='Z') k++;
	}

	if (j < 1 || k < 1) {
		write("�Բ��������������������ֺ�Ӣ�Ĵ�д��ĸ��\n");
		write("�������������룺");
		input_to("new_password", 1, ob);
		return;
	}

	if (strsrch(lower_case(pass), ob->query("id")) >= 0) {
		write("�Բ�����������̫�򵥡�\n");
		write("�������������룺");
		input_to("new_password", 1, ob);
		return;
	}

	ob->set("password", crypt(pass, "$1$ShuJian"));
	write("\n��������һ���������룬��ȷ����û�Ǵ���");
	input_to("confirm_password", 1, ob);
}

private void confirm_password(string pass, object ob)
{
	string old_pass = ob->query("password");

	write("\n");
	if (crypt(pass, old_pass) != old_pass) {
		write("��������������벻һ�����������趨���룺");
		input_to("new_password", 1, ob);
		return;
	}
	write(
"\n"
"���������ĸ��մ���������������ִ��������������Ժ���������ģ�\n"
"����������������Ź۵���������ɾ������\n"
HIY "���棺��Ҫʹ�ý�ӹС˵�е����������ͳ��óƺ���\n"
"      ��Ҫʹ����Ϸ���Ѿ����ڵ����������ͳ��óƺ���\n" NOR
"\n"
);
	write("�����������֣�");
	input_to("get_name", ob);
}

private string display_attr(int gift)
{
	if (gift > 24) return HIY + gift + NOR;
	if (gift < 16) return CYN + gift + NOR;
	return "" + gift;
}

private void get_name(string arg, object ob)
{
	if (!check_legal_name(ob, arg)) {
		write("�����������֣�");
		input_to((: get_name :), ob);
		return;
	}
	ob->set("name", arg);

	write("\n\n"
		"һ��������츳��������������ϰ������ϢϢ��ء�\n"
		+ MUD_NAME + "�е�����������������츳��\n\n"
		" 1. ������Ӱ���˺���������������������������������������\n"
		" 2. ���ԣ�Ӱ��ѧϰ�ٶȡ����������;���������\n"
		" 3. ���ǣ�Ӱ�������ָ��ٶȡ����˳������������������������\n"
		" 4. ������Ӱ���������;�����������\n\n"
		"�������Լ�ָ������һ���ֵ���������� 0 ��ϵͳ���������\n"
		"����������ѡ��(0-4)��"
	);
	input_to("select_gift", ob);
}

private void get_gift(string yn, object ob, mapping my, int select)
{
	if (lower_case(yn)[0] != 'y') {
		random_gift(my, select);
		write(sprintf("\n����[%s]������[%s]������[%s]������[%s]\n��ͬ����һ���츳��",
			display_attr(my["str"]),
			display_attr(my["int"]),
			display_attr(my["con"]),
			display_attr(my["dex"]))
		);
		input_to((: get_gift :), ob, my, select);
		return;
	}
        write("\n���ĵ����ʼ���ַ��");
        input_to("get_email", ob, my);
}

private void select_gift(string yn, object ob)
{
	int i;

	if (!sscanf(yn, "%d", i) || i < 0 || i > 4) {
		write("\n�������������ѡ��");
		input_to("select_gift", ob);
		return;
	}
	if (i) {
		write("\n����������Ҫ����ֵ(10-30)��");
		input_to("set_gift", ob, ([]), i);
	} else get_gift(" ", ob, ([]), i);
}

private void set_gift(string yn, object ob, mapping my, int select)
{
	int i;

	if (!sscanf(yn, "%d", i) || i < 10 || i > 30) {
		write("\n��ֵ�������������룺");
		input_to("set_gift", ob, my, select);
		return;
	}
	switch (select) {
		case 1: my["str"] = i; break;
		case 2: my["int"] = i; break;
		case 3: my["con"] = i; break;
		case 4: my["dex"] = i;
	}
	get_gift(" ", ob, my, select);
}

private void get_email(string email, object ob, mapping my)
{
	object user;

	write("\n");
	if (email == "" || strsrch(email, "@") < 2) {
		write("�����ʼ���ַ������ id@address �ĸ�ʽ��\n");
		write("���ĵ����ʼ���ַ��");
		input_to("get_email", ob, my);
		return;
	}
	ob->set("email", email);
	// If you want do race stuff, ask player to choose one here, then you can
	// set the user's body after the question is answered. The following are
	// options for player's body, so we clone a body here.
	ob->set("body", USER_OB);
	if (!objectp(user = make_body(ob))) {
		destruct(ob);
		return;
	}
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	user->set("str", my["str"]);
	user->set("dex", my["dex"]);
	user->set("con", my["con"]);
	user->set("int", my["int"]);
	user->set("kar", my["kar"]);
	user->set("per", my["per"]);

	if (ob->query("id") != "guest") {
		ob->set("registered", 1);
		user->set("registered", 1);
	}

	write("��Ҫ��������(m)�Ľ�ɫ��Ů��(f)�Ľ�ɫ��");
	input_to("get_gender", ob, user);
}

private void get_gender(string gender, object ob, object user)
{
	write("\n");
	if( gender=="" ) {
		write("��Ҫ��������(m)�Ľ�ɫ��Ů��(f)�Ľ�ɫ��");
		input_to("get_gender", ob, user);
		return;
	}

	switch (lower_case(gender)[0]) {
		case 'm':
			user->set("gender", "����");
			break;
		case 'f':
			user->set("gender", "Ů��" );
			break;
		default:
			write("�Բ�����ֻ��ѡ������(m)��Ů��(f)�Ľ�ɫ��");
			input_to((: get_gender :), ob, user);
			return;
	}

	log_file( "USAGE", sprintf("%-19s�� %-16s����(%s)\n",
		user->query("name")+"("+capitalize(""+user->query("id"))+")",
		query_ip_number(ob), ctime(time())[4..18]));
	init_new_player(user);
	enter_world(ob, user);
}

object make_body(object ob)
{
	object user;

	if (previous_object() && getuid(previous_object()) != ROOT_UID)
		return 0;
	user = new(ob->query("body"));
	if (!user) {
		write("���ڿ������������޸�ʹ��������ĳ����޷����и��ơ�\n\n");
		return 0;
	}
	seteuid(ob->query("id"));
	export_uid(user);
	export_uid(ob);
	seteuid(getuid());
	user->set_name(ob->query("name"), ({ ob->query("id")}));
	return user;
}

private void init_new_player(object user)
{
	user->set("title", "��ͨ����");
	user->set("birthday", time());
	user->set("potential", 99);
	user->set("food", 200);
	user->set("water", 200);
	user->set("env/wimpy", 50);
	user->set("freeuser",1);//��ע�����
	user->set("enter_wuguan", 1);
	user->set("channels", ({ "chat", "rumor", "party", "sj", "declare" }));
}

varargs void enter_world(object ob, object user, int silent)
{
	object mbx;
	string startroom;
	int num;

	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	user->set_temp("big5", ob->query_temp("big5"));
	user->set("registered", ob->query("registered"));
        user->set("registered",3);
	if (!silent && !wiz_level(user->query("id")))
		if (user->query("registered") < 2) write(""+read_file(UNREG_MOTD));
		else write(""+read_file(MOTD));

	ob->set_temp("last_from", query_ip_name(ob)+"("+query_ip_number(ob)+")");
	exec(user, ob);
	tell_object(user, "\n��Ŀǰ��Ȩ���ǣ�" + wizhood(user) + "\n");
	user->setup();

	// In case of new player, we save them here right aftre setup
	// compeleted.
	user->save();
	ob->save();

	UPDATE_D->get_cloth(user);

	if( !silent ) {
		user->set_temp("last_damage_from", "�������¶�ʧ�˺�Դ");
		user->set_temp("mud_age", user->query("mud_age"));
//add by hxsdΪ������.
user->set("registered",3);
		if (user->query("registered") > 1) {

			if (!stringp(startroom = user->query("startroom")))
				startroom = START_ROOM;
			if (user->query("enter_wuguan"))
				startroom = START_ROOM;
			if (user->is_ghost())
				startroom = DEATH_ROOM;
			if (wizardp(user))
				if (file_size("/u/"+user->query("id")+"/workroom.c") > 0)
					startroom = "/u/"+user->query("id")+"/workroom";
				else
					startroom = "/d/wizard/wizard_room";

			if (!load_object(startroom)) {
				write("���ϴ��˳��ĵط��Ѿ���ʧ�ˡ�\n");
				startroom = START_ROOM;
			}
					
			user->move(startroom);
			user->set("startroom", startroom);
		} else
			user->move(REGISTER_ROOM);

		startroom = ob->query("last_from");
		if (stringp(startroom))
			sscanf(startroom, "%*s(%s)", startroom);
		if (ob->query("last_on"))
			write("���ϴ����ߵ�ַ�� " HIR + startroom + NOR
				" �� " HIR + ctime(ob->query("last_on"))[4..18] + NOR "\n");
		if (num = ob->query("login_fail")) {
			write("�����ϴ��˳������ε�¼�ڼ䣬����"+chinese_number(num)+"��ʧ�ܵĵ�¼��ͼ��\n");
			ob->delete("login_fail");
			ob->save();
		}
				if (!wizardp(user) && !__DIR__"named"->valid_name(user->query("name"))){
			write(HIY BLINK"�����������ֲ������齣���������򣬻��������ظ����뾡����ġ�\n" NOR);
			write(HIY "���õ�һ������޸��������ֵĻ��ᣬ��ȥ���ݳ��ҡ��Գ�֮�������޸ġ�\n" NOR);
		}

		if (!wizardp(user) || !user->query("env/invisibility"))
			tell_room(environment(user), user->short() + "���߽���������硣\n", user);

                 "/cmds/std/vote"->main(user);
                "/cmds/std/msg"->main(user);
                "/cmds/usr/time"->do_vip(user);
                "/cmds/usr/news"->list_news(user, 1);
                  if (wizardp(user))
                        "/cmds/usr/sos"->sos_list(user, "no_solved");

  		mbx = new(MAILBOX_OB);
		mbx->set_owner(user->query("id"));
		num = mbx->query_new_mail();
		if (num > 0) {
			write( HIR + "\n�齣������Ϸ֪ͨ�㣺����"
				+chinese_number(num)+"���ţ��뵽��վ��һ�ˣ�����\n\n" + NOR
			);
		}
		destruct(mbx);
	}
	
	
	//renlai �����¿���½
	if (!(user->query("buyvip") || user->query("y-card-vip")) && (__DIR__"sited"->is_multi2(user->query("id"),query_ip_number(user),"")))
	{
		user->set("last_on",time());
		write(HIG+"\n---------------------->��վ����˺����������ƣ��꿨�˺����������ơ�\n\n"+NOR);
		ob->set("last_on",time());
		ob->save();
		user->save();
		command("quit");
		destruct(user);
		return;		
	}

	user->set_temp("combat_exp", user->query("combat_exp"));
	user->set_temp("time", uptime());
	user->set_temp("robottest", uptime() - 1500);

	CHANNEL_D->do_channel(this_object(), wiz_level(user)?"wiz":"sys",
		sprintf("%s �� " HIG "%s" NOR " ���߽��롣", user->short(1),
		query_ip_name(user)+"("+query_ip_number(user)+":"+query_ip_name(user)+")")
	);

	num = time()-ob->query("last_on");
	if (num < 21600 && stringp(startroom)) {
		string now = IP_D->ip2name(query_ip_number(user));

		startroom = IP_D->ip2name(startroom);
		if (startroom[0..3] != now[0..3])
			CHANNEL_D->do_channel(this_object(), "wiz",
				sprintf("%s%sǰ��" HIG "%s" NOR "��Ŀǰ��" HIG "%s" NOR "���߽���",
					user->short(1), CHINESE_D->chinese_time(num),
					startroom, now)
			);
	}
}

varargs void reconnect(object ob, object user, int silent)
{
	string startroom = ob->query("last_from");

	if (stringp(startroom)) {
		string now = IP_D->ip2name(query_ip_number(ob));

		sscanf(startroom, "%*s(%s)", startroom);
		startroom = IP_D->ip2name(startroom);
		if (startroom[0..3] != now[0..3])
			CHANNEL_D->do_channel(this_object(), "wiz",
				sprintf("%s%sǰ��" HIG "%s" NOR "��Ŀǰ��" HIG "%s" NOR "���߽���",
					user->short(1), CHINESE_D->chinese_time(time()-ob->query("last_on")),
					startroom, now)
			);
	}
	user->set_temp("link_ob", ob);
	ob->set_temp("body_ob", user);
	user->set_temp("big5", ob->query_temp("big5"));
	ob->set_temp("last_from", query_ip_name(ob)+"("+query_ip_number(ob)+")");
	exec(user, ob);
	
	
	//��ֹ����
	
	//renlai �����¿���½
	if (!(user->query("buyvip") || user->query("y-card-vip")) && (__DIR__"sited"->is_multi2(user->query("id"),query_ip_number(user),"")))
	{
		user->set("last_on",time());
		write(HIG+"\n---------------------->��վ����˺����������ƣ��꿨�˺����������ơ�\n\n"+NOR);
		ob->set("last_on",time());
		ob->save();
		user->save();
		command("quit");
		destruct(user);
		return;		
	}
	
	
	user->reconnect();

	
	if (!silent && (!wizardp(user) || !user->query("env/invisibility")))
		tell_room(environment(user), user->name() + "�������߻ص�������硣\n", user);
	CHANNEL_D->do_channel( this_object(), wiz_level(user)?"wiz":"sys",
		sprintf("%s �� " HIG "%s" NOR " �������߽��롣", user->short(1), query_ip_name(user))
	);
}

int check_legal_id(string id)
{
	int i;
	string *legalid; //��ֹĳЩID��¼

	i = strlen(id);

	if( i < 3 || i > 8 ) {
		write("�Բ�������Ӣ�����ֱ����� 3 �� 8 ��Ӣ����ĸ��\n");
		return 0;
	}

	while(i--)
		if( id[i] < 'a' || id[i] > 'z' ) {
			write("�Բ�������Ӣ������ֻ����Ӣ����ĸ��\n");
			return 0;
		}

	legalid = explode(read_file(BANNED_ID), "\n");
	foreach(string item in legalid)
		if (id == item) {
			write("�Բ������������Ѿ�����ֹʹ�á�\n");
			return 0;
		}
	return 1;
}

int check_legal_name(object ob, string name)
{
	int i;

	i = strlen(name);

	if (i < 4 || i > 8 || i%2) {
		write("�Բ��������������ֱ����� 2 �� 4 �������֡�\n");
		return 0;
	}

	while(i--)
		if (i%2==0 && !is_chinese(name[i..<1])) {
			write("�Բ��������á����ġ�ȡ���֡�\n");
			return 0;
		}

	if (!wiz_level(ob->query("id"))	&& !__DIR__"named"->valid_name(name)) {
		write("�Բ����������ֻ���������˵����š�\n");
		return 0;
	}

	return 1;
}

object find_body(string name)
{
	object ob, *body;

	if( objectp(ob = find_player(name)) )
		return ob;
	body = children(USER_OB);
	foreach(ob in body) if (getuid(ob) == name) return ob;
	return 0;
}

int set_wizlock(int level)
{
	if( wiz_level(this_player(1)) < level )
		return 0;
	if( geteuid(previous_object()) != ROOT_UID )
		return 0;
	wiz_lock_level = level;
	return 1;
}