inherit F_DBASE;
#include <ansi.h>
#include <mudlib.h>

nosave mapping valid_login = ([
	// 总站巫师
           "jeep":      ({ "117.66","127","60.171" }),
           "master":    ({ "222", "124.", "58.","116" }),                 
           //"hongba":    ({ "222", "124.", "218.","116" }),                 
 
       	]);

void add_site(string id, string addr)
{
	if (!stringp(id) || !stringp(addr)) return;
	if (arrayp(valid_login[id])) valid_login[id] += ({ addr });
	else valid_login[id] = ({ addr });
}

void del_site(string id, string addr)
{
	if (!stringp(id) || !stringp(addr)) return;
	if (arrayp(valid_login[id])) valid_login[id] -= ({ addr });
}

string *query_site(string id)
{
	if (stringp(id)) return valid_login[id];
	return 0;
}

int is_valid(string id, string ip)
{
	int i;
	int ip1, ip2;

	if (sscanf(ip, "%d.%d.%*d.%*d", ip1, ip2) != 4) return 0;

	// 内部网地址 YUJ@SJ 2002-01-30
	if (ip1 == 10) return 1;
	if (ip1 == 172 && ip2 & 240 == 16) return 1;
	if (ip1 == 192 && ip2 == 168) return 1;

	if (undefinedp(valid_login[id+"@"+INTERMUD_MUD_NAME])) {
		if (undefinedp(valid_login[id])) {
			if (!wiz_level(id)) return 1;
			write("巫师必须有地址限制，请用 guest 登录通知天神。\n");
			destruct(this_object());
			return 0;
		}
	} else id += "@"+INTERMUD_MUD_NAME;
	i = sizeof(valid_login[id]);
	while (i--) if (sscanf(ip, valid_login[id][i] + "%*s")) return 1;
	destruct(this_object());	// 自动摧毁自己，方便YUJIP改变刷新
	return 0;
}

mapping valid_multi = ([
	"":		0,
]);

int is_multi(string id, string ip, string port)
{
	object *usr;
	string *site = keys(valid_multi);
	int i, login_cnt = 0;
	string ipname = IP_D->ip2name(ip);

	if (query(ip) && query(ip) != port) {
		write("您的地址刚有人登录，请等会再试。\n");
		return 1;
	}
	set(ip, port);
	call_out("delete", 10, ip);
	usr = filter_array(users(), (: environment :));
	i = sizeof(usr);
	while (i--) {
		if (query_ip_number(usr[i]) != ip) continue;
		if (usr[i]->query("id") != id) {
/*
			if (wiz_level(id)) {
				write("对不起，您的地址已经有玩家连线，禁止登录。\n");
				return 1;
			}
			if (wiz_level(usr[i])) {
				write("对不起，您的地址已经有巫师连线，禁止登录。\n");
				return 1;
			}
*/
			login_cnt++;
		}
	}
	write(CSI "20D您的 IP 是：" HIW + ip + ":" + port + "(" + ipname + ")" NOR "，此地址另有" + chinese_number(login_cnt)+"位玩家在线。\n");
	if (ipname == "未知"){
		message("wizard:anger", id + " " + ip + "\n", usr);
		message("wizard:jeep", id + " " + ip + "\n", usr);
	}

	//	if (!login_cnt) return 0;
	// By Spiderii 加入IP限制
	if (login_cnt > 10)
	{
		write("对不起，您目前的地址已到达人数限制，请退出其他ID以便登陆。\n");
		return 1;
	}

	i = sizeof(valid_multi);
	while (i--) if (sscanf(ip, site[i] + "%*s")) break;
	if (i < 0) {
		write("对不起，您目前的地址禁止多重登录，请与巫师联系。\n");
		return 1;
	}
	if (!(i = valid_multi[site[i]])) return 0;
	if (login_cnt < i) return 0;
	write("对不起，您目前的地址已到达人数限制，请与巫师联系。\n");
	return 1;
}

int is_multi2(string id, string ip,string port)
{
	
	object *usr;
	string *site = keys(valid_multi);
	int i, login_cnt,vip_cnt = 0;
	string ipname = IP_D->ip2name(ip);

	if (query(ip) && query(ip) != port) {
		write("您的地址刚有人登录，请等会再试。\n");
		return 1;
	}	
	set(ip, port);
	call_out("delete", 10, ip);
	
	usr = filter_array(users(), (: environment :));
	
	i = sizeof(usr);
	
	while (i--) {
		if (query_ip_number(usr[i]) != ip) continue;
		if (usr[i]->query("y-card-vip") || usr[i]->query("buyvip"))
        {
			vip_cnt++;
			continue;
		}
		if (usr[i]->query("id") != id) {
			login_cnt++;
		}
	}	
	write(CSI "20D您的IP是：" HIW + ip + ":" + port + "(" + ipname + ")" NOR "，此地址另有" + chinese_number(login_cnt) + "位免费账号和" + chinese_number(vip_cnt)+ "位贵宾账号在线。\n");
	
	if (ipname == "未知"){
		message("wizard:anger", id + " " + ip + "\n", usr);		
	}	
	
	if (login_cnt > 4)  //限制同ip登录为5人
	{
		write("对不起，您目前的地址已到达免费账号数限制，请退出其他ID以便登陆。\n");
		return 1;
	}

	i = sizeof(valid_multi);
	while (i--) if (sscanf(ip, site[i] + "%*s")) break;
	if (i < 0) {
		write("对不起，您目前的地址禁止多重登录，请与巫师联系。\n");
		return 1;
	}
	if (!(i = valid_multi[site[i]])) return 0;
	if (login_cnt < i) return 0;
	write("对不起，您目前的地址已到达人数限制，请与巫师联系。\n");
	
	return 1;
}

