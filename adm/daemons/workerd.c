/*
Workerd
Created	by snowman@SJ 21/04/2001
Modified by augx@SJ 9/6/2001
Modified by Ciwei@SJ

Copyright 1997-2001 ShuJian MUD Wizard Group.
All rights reserved.

*/

// Modified by mxzhao 2004/03/06 caiji => nongsang, caijian => zhizao

inherit F_SAVE;

#include <ansi.h>
#include <mudlib.h>
#include <net/socket.h>
#include <socket_err.h>
#include <worker.h>
#include <database.h>

#define OBJ_DIR         "/clone/zhiye/"
#define WORKER_FILE	DATA_DIR + "career/"
#define MATERIAL_LEVEL 11
#define RANK_TOTAL 100
#define NO_LOGIN_D 7
/////////////////////////// functions ///////////////////////////////
int sort_rank(mapping rank1, mapping rank2);

string imbued_object_type(string save_id);
string worker_title(object me,string type);

mapping convert_user2armor(mapping mp);
mapping convert_armor2user(mapping mp);
mapping convert_user2weapon(mapping mp);
mapping convert_weapon2user(mapping mp);

mapping	make_user_weapon_random(object me, string type, int qua, string material,mapping shuxing,string* status);
object make_weapon(object me, mixed type, int qua, string material,mapping shuxing,string* status);
int weapon_rank(object wp);

mapping	make_user_armor_random(object me, string type, int qua, string material,mapping shuxing,string* status);
object make_armor(object me, mixed type, int qua, string material,mapping shuxing,string* status);
int armor_rank(object wp);

//int update_UniqueValues(string var,string var2,string callback);
//int query_UniqueValues(string var,string callback);
//int addto_pool(string pool,string id,string var);
/////////////////////////////////////////////////////////////////////

nosave int imbue_sta = 0;
nosave string imbue = "";

int sum(int n,int d)
{
        return (n*(2*10+(n-1)*d)/2);
}

void imbue_s(string arg)
{
	imbue =	arg;
}

void imbue_q(int arg)
{
	imbue_sta = arg;
}

string imbued_object_type(string save_id)
{
	if( !stringp(save_id) || strlen(save_id)<10 ) return "bugtype";
	switch ( save_id[<1..<1] ) {
		case "a": return "armor";
		case "d": return "drug";
		case "w":
		default: return "weapon";
	}
}

string worker_title(object me,string type)
{
	int level;

	string str="BUG!!!";

	if ( !me || !stringp(type) || strlen(type)<3 )
	{
		return str;
	}

	level = (int)me->query_skill(type, 1);

	if( type == "duanzao" )
	{
		if(level<60) str=GRN"铸剑师学徒"NOR;
		else if(level<120) str=CYN"初级铸剑师"NOR;
		else if(level<180) str=RED"铸剑师"NOR;
		else if(level<240) str=YEL"高级铸剑师"NOR;
		else if(level<300) str=HIG"优秀铸剑师"NOR;
		else if(level<350) str=HIC"神奇铸剑师"NOR;
		else if(level<390) str=HIR"神圣铸剑师"NOR;
		else if(level<400) str=HIY"传奇铸剑师"NOR;
		else str=HIW"传说中的铸剑师"NOR;
	}
	else if( type == "zhizao" )
	{
		if(level<60) str=GRN"裁缝学徒"NOR;
		else if(level<120) str=CYN"见习裁缝"NOR;
		else if(level<180) str=RED"裁缝"NOR;
		else if(level<240) str=YEL"高级裁缝"NOR;
		else if(level<300) str=HIG"优秀裁缝"NOR;
		else if(level<350) str=HIC"织造师"NOR;
		else if(level<390) str=HIR"高级织造师"NOR;
		else if(level<400) str=HIY"织造大师"NOR;
		else str=HIW"传说中的织造大师"NOR;
	}
	else if( type == "liandan" )
	{
		if(level<60) str=GRN"药师学徒"NOR;
		else if(level<120) str=CYN"药师助手"NOR;
		else if(level<180) str=RED"药师"NOR;
		else if(level<240) str=YEL"闻名药师"NOR;
		else if(level<300) str=HIG"著名药师"NOR;
		else if(level<350) str=HIC"神奇药师"NOR;
		else if(level<390) str=HIR"神圣药师"NOR;
		else if(level<400) str=HIY"传奇药师"NOR;
		else str=HIW"传说中的药师"NOR;
	}

	return str;
}

protected void delete_user_weapon(object me, string save_id, string text)
{
	if( !me ) return;
	if( text ) write(HIW"您的兵器因为：" + text + "，被系统取消。\n"NOR);
	me->delete("worker/"+save_id);
	me->save();
	log_file("career/worker", sprintf("delete  :%-8s:%-19s:%s\n",me->query("id"),save_id,text), me);
}

protected void delete_user_armor(object me, string save_id, string text)
{
	if( !me ) return;
	if( text ) write(HIW"您的防具因为：" + text + "，被系统取消。\n"NOR);
	me->delete("worker/"+save_id);
	me->save();
	log_file("career/worker", sprintf("delete  :%-8s:%-19s:%s\n",me->query("id"),save_id,text), me);
}

public void deleteweapon(string id,string str,string sid)
{
	object body;
	seteuid(ROOT_UID);	
	if(objectp(body = LOGIN_D->find_body(id))) {
		body->delete( "worker/" + sid );
		if(str) message("channel",HIW+str+NOR,({body}));
	}
	else
	{
		object ob;		
		ob = new(LOGIN_OB);
		ob->set("id", id);
		if(!ob->restore()) {destruct(ob);return;}
		body = LOGIN_D->make_body(ob);
		if( body->restore() ) {
			body->delete( "worker/" + sid );
			if(str) "/cmds/std/msg"->system_send(this_object(),({id}),"私有物品被删", HIW+"在您离线期间：\n"+str+NOR );
			body->set_temp("db_quit",1);
			body->save();
		}
		destruct(ob);
		destruct(body);
	}
}


object load_user_object(object me,mapping u_map)
{
	mapping	w_map;
	object weapon,armor,drug;
	int j;

	if ( imbued_object_type(u_map["save_id"])=="weapon" ) {
		w_map =	DEFAULT_SETTINGS;
		switch(u_map["imbued"]){
			case 5: w_map += copy(SUPER_B); break;//to SUPER_B temp
			case 4: w_map += copy(SUPER_B); break;
			case 3: w_map += copy(GREAT_B); break;
			case 2: w_map += copy(GOOD_B); break;
			default: break;
		}
		w_map += convert_user2weapon(u_map);

		weapon = make_weapon(me, w_map, 0, 0,0,0);
		if( weapon ) {
			if ( weapon->query("weapon_mp/imbued")>3 ) {
				j = weapon->query("weapon_mp/utime");
				/*
				if( (time()-j) > 432000 && weapon->query("owner")!=getuid(me) ) { // 5 day
					tell_object(me,"\n由于长时间没有上线，你的兵器"+weapon->query("name")+"消失了！\n\n");
					log_file("career/worker", sprintf("overtime:%-8s:%s:%s\n",me->query("id"),weapon->query("weapon_mp/save_id"),ctime(j)), me);
					weapon->delete_weapon(me);
					destruct(weapon);
					return 0;
				}
				*/
				weapon->set("weapon_mp/utime", time());
				//addto_pool("update",weapon->query("weapon_mp/save_id"),sprintf("%d,score=%d",time(),weapon_rank(weapon)));
			}
			weapon->move(me);
		}
		return weapon;
	}

	if ( imbued_object_type(u_map["save_id"])=="armor" ) {
		w_map =	ARMOR_DEFAULT_SETTINGS;
		switch(u_map["imbued"]){
			case 5: w_map += copy(ARMOR_SUPER_B); break;//ARMOR_SPECIAL_B to ARMOR_SUPER_B
			case 4: w_map += copy(ARMOR_SUPER_B); break;
			case 3: w_map += copy(ARMOR_GREAT_B); break;
			case 2: w_map += copy(ARMOR_GOOD_B); break;
			default: break;
		}
		w_map += convert_user2armor(u_map);

		armor = make_armor(me, w_map, 0, 0,0,0);
		if( armor ) {
			if ( armor->query("armor_mp/imbued")>3 && armor->query("owner")!=getuid(me)  ) {
				j = armor->query("armor_mp/utime");
				/*
				if( (time()-j) > 432000 ) { // 5 day
					tell_object(me,"\n由于长时间没有上线，你的防具"+armor->query("name")+"消失了！\n\n");
					log_file("career/worker", sprintf("overtime:%-8s:%s:%s\n",me->query("id"),armor->query("armor_mp/save_id"),ctime(j)), me);
					armor->delete_armor(me);
					destruct(armor);
					return 0;
				}
				*/
				armor->set("armor_mp/utime", time());
				//addto_pool("update",armor->query("armor_mp/save_id"),sprintf("%d,score=%d",time(),armor_rank(armor)));
			}
			armor->move(me);
		}
		return armor;
	}

	if ( imbued_object_type(u_map["save_id"])=="drug" ) {
		drug = new("/clone/zhiye/yao");
		if(drug) {
			drug->drug_setup(u_map);
			drug->move(me);
		}
	}
}

void check_user_object(object me)
{
	mapping	u_map;
	mixed worker_array;
	object * inv;
	int i;
	string log = "";
	// object link_ob,obj;

	if( !mapp(me->query("worker")) ) return;
	worker_array = values(me->query("worker"));
	for(i=0;i<sizeof(worker_array);i++) {
		if ( mapp(u_map = worker_array[i]) && stringp(u_map["save_id"]) )
			load_user_object(me , u_map);
	}

	inv = all_inventory(me);
	if( !arrayp(inv) || sizeof(inv)<1 ) return;
	for(i=0;i<sizeof(inv);i++) {
		if ( stringp(inv[i]->query("save_id")) )
			log += inv[i]->query("save_id") + ",";
	}
	if( strlen(log) > 3 )
		log_file("career/worker", sprintf("login   :%-8s:%s",me->query("id"),log), me);

	/*
	if(me->query("id")=="river") {
		seteuid(ROOT_UID);
		obj = LOGIN_D->find_body(me->query("id"));
		obj->dismiss_team();
		obj->save();
		link_ob = obj->query_temp("link_ob");
		if (link_ob) {
			link_ob->save();
			destruct(link_ob);
		}
		catch(destruct(obj));
	}
	*/
}

///////////////////// convert mapping functions /////////////////////
//owner->user super_user->owner
mapping convert_armor2user(mapping mp)
{
	mapping my_mp = ([ ]);
	string st;

	if( stringp(mp["name_st"]) )
		st = mp["name_st"];
	else if( sizeof(mp["name_st"]) > 0 )
		st = implode(mp["name_st"][0..<1], "、");

	my_mp["imbued"] 	=	mp["imbued"];
	my_mp["save_id"] 	=	mp["save_id"];
	my_mp["id"] 		=	mp["id"];
	my_mp["armor_prop"]	=	mp["armor_prop"];
	my_mp["user"]		=	mp["user"];	// 持有人
	my_mp["ltime"]		=	mp["ltime"];	// 上次维护时间

	if (mp["armor_type"] == TYPE_CLOTH)
		mp["armor_type"] = TYPE_COAT;

	my_mp["var"] = sprintf("%s,%s,%d,%d,%d,%d,%d,%s,%s,%d,%d,%s,%d,%d,%d,%d,%d,%s,%s,%s,%s",
			mp["armor_type"],
			mp["unit"],
			mp["weight"],
			mp["value"],
			mp["wear_str"],
			mp["wear_con"],
			mp["wear_maxneili"],
			mp["material"],
			mp["name"],
			mp["dur"],
			mp["max_dur"],
			mp["poisoned"],
			mp["poison_number"],
			mp["utime"],
			mp["storeneili"],
			mp["storetimes"],
			mp["decdamage"],
			st,
			mp["maker"],
			mp["long2"],
			mp["owner"]
		);

	return my_mp;
}

mapping convert_user2armor(mapping mp)
{
	mapping my_mp = ([ ]);

	my_mp["imbued"] 	=	mp["imbued"];
	my_mp["save_id"] 	=	mp["save_id"];
	my_mp["id"] 		=	mp["id"];
	my_mp["armor_prop"]	=	mp["armor_prop"];
	my_mp["user"]		=	mp["user"];	// 持有人
	my_mp["ltime"]		=	mp["ltime"];	// 上次维护时间

	sscanf(mp["var"] , "%s,%s,%d,%d,%d,%d,%d,%s,%s,%d,%d,%s,%d,%d,%d,%d,%d,%s,%s,%s,%s",
		my_mp["armor_type"],
		my_mp["unit"],
		my_mp["weight"],
		my_mp["value"],
		my_mp["wear_str"],
		my_mp["wear_con"],
		my_mp["wear_maxneili"],
		my_mp["material"],
		my_mp["name"],
		my_mp["dur"],
		my_mp["max_dur"],
		my_mp["poisoned"],
		my_mp["poison_number"],
		my_mp["utime"],
		my_mp["storeneili"],
		my_mp["storetimes"],
		my_mp["decdamage"],
		my_mp["name_st"],
		my_mp["maker"],
		my_mp["long2"],
		my_mp["owner"]
	);

	if (my_mp["armor_type"] == TYPE_CLOTH)
		my_mp["armor_type"] = TYPE_COAT;

	return my_mp;
}

mapping convert_weapon2user(mapping mp)
{
	mapping my_mp = ([ ]);
	string st;

	if( stringp(mp["name_st"]) )
		st = mp["name_st"];
	else if( sizeof(mp["name_st"]) > 0 )
		st = implode(mp["name_st"][0..<1], "、");

	my_mp["imbued"] 	=	mp["imbued"];
	my_mp["save_id"] 	=	mp["save_id"];
	my_mp["id"] 		=	mp["id"];
	my_mp["weapon_prop"] 	=	mp["weapon_prop"];
	my_mp["user"]		=	mp["user"];	// 持有人
	my_mp["ltime"]		=	mp["ltime"];	// 上次维护时间

	my_mp["var"] = sprintf("%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%s,%s,%s,%s,%s",
			mp["skill_type"],
			mp["weight"],
			mp["flag"],
			mp["rigidity"],
			mp["sharpness"],
			mp["wield_str"],
			mp["wield_maxneili"],
			mp["wield_neili"],
			mp["value"],
			mp["dur"],
			mp["max_dur"],
			mp["material"],
			mp["poisoned"],
			mp["poison_number"],
			mp["utime"],
			mp["hammer_count"],
			mp["dagger_count"],
			mp["name"],
			st,
			mp["maker"],
			mp["long2"],
			mp["owner"],
		);

	return my_mp;
}

mapping convert_user2weapon(mapping mp)
{
	mapping my_mp = ([ ]);

	if( undefinedp(mp["var"]) ) return mp;

	my_mp["imbued"] 	=	mp["imbued"];
	my_mp["save_id"] 	=	mp["save_id"];
	my_mp["id"] 		=	mp["id"];
	my_mp["weapon_prop"]	=	mp["weapon_prop"];
	my_mp["user"]		=	mp["user"];	// 持有人
	my_mp["ltime"]		=	mp["ltime"];	// 上次维护时间

	sscanf(mp["var"], "%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%d,%d,%d,%d,%s,%s,%s,%s,%s",
		my_mp["skill_type"],
		my_mp["weight"],
		my_mp["flag"],
		my_mp["rigidity"],
		my_mp["sharpness"],
		my_mp["wield_str"],
		my_mp["wield_maxneili"],
		my_mp["wield_neili"],
		my_mp["value"],
		my_mp["dur"],
		my_mp["max_dur"],
		my_mp["material"],
		my_mp["poisoned"],
		my_mp["poison_number"],
		my_mp["utime"],
		my_mp["hammer_count"],
		my_mp["dagger_count"],
		my_mp["name"],
		my_mp["name_st"],
		my_mp["maker"],
		my_mp["long2"],
		my_mp["owner"]
	);

	return my_mp;
}

/////////////////////////// make weapon /////////////////////////////
object make_weapon(object me, mixed type, int qua, string material,mapping shuxing,string* status)
{
	mapping	w_mp;
	object wp;
	string str = "", st;
	int w, p, new_w=0;
	object* clone;

	if( stringp(type) ) {
		w_mp = make_user_weapon_random(me, type, qua, material,shuxing,status);

		if( !mapp(w_mp)	){
			write("Error! no w_mp! \n");
			return 0;
		}

		new_w = 1;
		special_st = name_st = ({ });
	}
	else if( mapp(type) ) {
		w_mp = type;
	}
	else return 0;
	
	str = w_mp["save_id"];
	clone = filter_array(children(USER_WEAPON), (: clonep :));
	for( w = 0;w<sizeof(clone); w++ ){
                if ( clone[w]->query("save_id") == str )
                        return 0;
        }
	str = "";
	if( stringp(w_mp["long2"]) && w_mp["long2"]!="" && w_mp["long2"]!="0")
		str = w_mp["long2"];
	str += "这是一柄由" + s_good(w_mp["rigidity"]) + "坚硬的";
	switch(w_mp["material"]){
		case "hantie":    str += HIC"万年寒冰铁"NOR;break;
		case "xuantie":	  str += WHT"玄铁"NOR; break;
		case "shentie":   str += RED"万年神铁"NOR; break;
		case "jintie":    str += HIY"金铁"NOR; break;
		case "ruanying":  str += HIW"软银"NOR; break;
		case "liuhuashi": str += RED"流花石"NOR; break;
		case "lushi":     str += HIG"绿石"NOR; break;
		case "ruantie":   str += YEL"软铁"NOR; break;
		case "shengtie":  str += YEL"生铁"NOR; break;
		case "qingtong":  str += GRN"青铜"NOR; break;
		default: str +=	"精钢";	break;
	}
	w = w_mp["weight"];
	str +=	"制成，重"+sprintf("%s", chinese_number(w/500)+"斤"+chinese_number((w%500)/50)+"两"+chinese_number((w%50)/5)+"钱")+"的"+w_mp["name"]+"。\n";

	if( new_w )
		p = w_mp["weapon_prop"]["damage"];
	else if( intp(w_mp["weapon_prop"]["damage"]) )
		p = w_mp["weapon_prop"]["damage"];
	else p = 0;

	if( w_mp["imbued"] < 5 && p > 300 && !new_w ){
		delete_user_weapon(me, w_mp["save_id"], "使用Bug致使威力过高");
		return 0;
	}
	else if( p <= 0 && !new_w){
		delete_user_weapon(me, w_mp["save_id"], "系统Bug致使毫无威力");
		return 0;
	}

	str += "看起来"	+ ( w_mp["flag"]==4?s_good(w_mp["sharpness"])+"锋利，":"" ) + "具有"+ s_power(p) + "的威力！\n";
	str += "装备要求：臂力【" +chinese_number(w_mp["wield_str"])+ "】，"
		+ "最大内力【" +chinese_number(w_mp["wield_maxneili"])+ "】，"
		+ "内力【" +chinese_number(w_mp["wield_neili"])+ "】\n";

	if( w_mp["name_st"] ) {
		if( stringp(w_mp["name_st"]) && strlen(w_mp["name_st"])>3 )
			str += "以及一排古篆字【 "HIG +	w_mp["name_st"]	+ NOR" 】\n";
		else if( arrayp(w_mp["name_st"]) && sizeof(w_mp["name_st"]) > 0 ) {
			st = implode(w_mp["name_st"][0..<1], "、");
			w_mp["name_st"] = st;
			str += "以及一排古篆字【 "HIG +	st + NOR" 】\n";
		}
	}

	if( stringp(w_mp["maker"]) && strlen(w_mp["maker"])>3 )
		str += "隐约能看见兵器制造者的姓名：" + w_mp["maker"] + "\n";
	
	if(stringp(w_mp["owner"]) && w_mp["owner"]!=""&& w_mp["owner"]!="0" && LOGIN_D->find_body(w_mp["owner"]) )
		str += "\n手柄上刻了几个小字："+LOGIN_D->find_body(w_mp["owner"])->query("name")+"("+capitalize(w_mp["owner"])+")\n";
		
	wp = new(USER_WEAPON);	
	wp->set("weapon_mp", copy(w_mp));
	wp->set("dur",w_mp["dur"]);

	if( wp->weapon_setup(copy(w_mp)) ){
		wp->set("weapon_mp/value" , weapon_rank(wp)*8*100);
		wp->set("value" , wp->query("weapon_mp/value") );
		wp->set("long" , str);
		//
		if (wizardp(me)) wp->set_temp("apply/long",({wp->short()+"\n"+wp->query("long")+WORKER_D->get_msg(wp->query("weapon_prop")) }));
		if( new_w && w_mp["imbued"]>2 ){
			// 记录格式：英文id：等级：中文名：类型：威力：评价
			log_file("career/zhujian", sprintf("%-19s:%d:%-20s:%-6s:%-3d:%d\n",w_mp["save_id"],w_mp["imbued"],w_mp["name"],w_mp["skill_type"],w_mp["weapon_prop"]["damage"],weapon_rank(wp)), me);
		}
		return wp;
	}
	else return 0;
}

// type	= weapon types.
// qua:	0 = normal, 1 =	good, 2	= great, 3 = super
nosave int debug_mode = 0;
nosave float tick_count2 = 1.0;
protected mapping make_user_weapon_random(object me,string type, int qua, string material,mapping shuxing,string* status)
{
	string wp_name,	name;
	string *types;
	int i,level,j;
	mixed add_num;
	mixed tempshuf;
	int tempshud;
	float c;
	string temp;
	int fristdb = 1;
			
	mp = DEFAULT_SETTINGS;
	
	if( member_array(type, keys(WEAPON_MAP)) != -1 )
		mp += copy(WEAPON_MAP[type]);
	else {
		write("Weapon Type out of range. \n");
		return 0;
	}

	if( imbue == "special" || qua == 4 ){
		qua = 5;
		qua = 4;
		i = random(sizeof(Super_Class));
		wp_name	= keys(Super_Class)[i];
		// Basic status	for Super class	weapons.
		mp += copy(SUPER_B);
		mp += ([ "weapon_prop":	(["damage" : 70 ]), ]);
		mp += Super_Class[wp_name];
		mp["id"] = ({ Super_Class[wp_name]["id"] + " " + type, Super_Class[wp_name]["id"], mp["b_id"], type });
		/*
		i = random(sizeof(Special_Class));
		wp_name	= keys(Special_Class)[i];
		mp += copy(SPECIAL_B);
		mp += Special_Class[wp_name];
		mp["id"] = ({ Special_Class[wp_name]["id"] + " " + type, Special_Class[wp_name]["id"], mp["b_id"], type });
		*/ 
		//暂时封存这些描述 xixi
	}
	else if( imbue == "super" || qua == 3 ){
		qua = 4;
		i = random(sizeof(Super_Class));
		wp_name	= keys(Super_Class)[i];
		// Basic status	for Super class	weapons.
		mp += copy(SUPER_B);
		mp += ([ "weapon_prop":	(["damage" : 50 ]), ]);
		mp += Super_Class[wp_name];
		mp["id"] = ({ Super_Class[wp_name]["id"] + " " + type, Super_Class[wp_name]["id"], mp["b_id"], type });
	}
	else if( imbue == "great" || qua == 2 ){
		qua = 3;
		i = random(sizeof(Great_Class));
		wp_name	= keys(Great_Class)[i];
		// Basic status	for Great class	weapons.
		mp += copy(GREAT_B);
		mp += ([ "weapon_prop":	(["damage" : 30 ]), ]);
		mp["id"] = ({ Great_Class[wp_name] + " " + type, Great_Class[wp_name], mp["b_id"], type	});
	}
	else if( imbue == "good" || qua	== 1 ){
		qua = 2;
		// Basic status	for good class weapons.
		wp_name	= G_3_class[random(sizeof(G_3_class))];
		mp += copy(GOOD_B);
		mp += ([ "weapon_prop":	(["damage" : 20 ]), ]);
		mp["id"] = ({ "good "+type, mp["b_id"] , type});
	}
	else {
		// Basic status	for normal class weapons.
		qua = 1;
		mp += ([ "weapon_prop":	(["damage" : 1 ]), ]);
		wp_name	= mp["basic_name"];
		mp["id"] = ({ "normal "+type, mp["b_id"], type });
	}
	////对于所有damage计算 是否对que=5屏蔽 这里留个意
	if(debug_mode) tell_object(me,sprintf("默认的%d\n",mp["weapon_prop"]["damage"]));
	imbue =	"";
	mp["basic_name"] = wp_name;
	mp["material"] = material;
	if( qua >= 3 ) mp["utime"] = time();
	mp["max_dur"] = mp["dur"];

	mp["weight"] = mp["weight"]*2/3 + random(mp["weight"]*2/3);
	mp["wield_maxneili"] = mp["wield_maxneili"]*2/3 + random(mp["wield_maxneili"]*2/3)+100;
	mp["wield_neili"] = mp["wield_neili"]*2/3 + random(mp["wield_neili"]*2/3);
	mp["wield_str"] = mp["wield_str"]*2/3 + random(mp["wield_str"]*2/3);
		
	///j = qua;	
	/*
	j = status;
	while(j--) {
		i = special_weapon_status(0,qua);
		if(i==3) break;
		if(i==2) { if(k==1) break; else k=1; }
	}
	*/	
	level = me->query_skill("duanzao",1);
	if(level<220) c = 0.002272*level;
	else if(level<400) c= 0.5+0.002778*(level-220);
	//if(level<600)
	else c= 1 + 0.005*(level-400);
	if(c>2) c = 2;//限制到600 level xixi		
	
	mp["weapon_prop"]["damage"] += to_int(15*c);
	if(debug_mode) tell_object(me,sprintf("由铁匠技能改变的的%d\n",mp["weapon_prop"]["damage"]));
	
	if(mapp(shuxing)){
		types = keys(shuxing);
		if(sizeof(types)>0) {for(i=0;i<sizeof(types);i++) mp["weapon_prop"][types[i]] += to_int(shuxing[types[i]]*c*(random(me->query_kar())+91)/100) ;}
	}
	if(debug_mode) tell_object(me,sprintf("加入玉的影响的%d\n",mp["weapon_prop"]["damage"]));
	
	j = sizeof(status);	
	while(j--)
	{		
		temp = status[j];
                fristdb=1;
 		        if(sscanf(temp,"status_type%dspe_name%sjade_show%sitem_show%sis_prop%dis_sure%dadd_type%sadd_use%dadd_num%scan_wield%sjust_for%ssta_over%s",
				status_type,spe_name,jade_show,item_show,is_prop,is_sure,add_type,add_use,add_num,can_wield,just_for,temp)==12)
			while( (fristdb==1 || temp!=" ") && spe_name!=" "){
				if(fristdb==1){
					special_st +=({ spe_name });
					name_st	+=({ item_show });}
				if(fristdb==0) if(sscanf(temp," next_add_ is_prop%dis_sure%dadd_type%sadd_use%dadd_num%scan_wield%sjust_for%ssta_over%s",
						is_prop,is_sure,add_type,add_use,add_num,can_wield,just_for,temp)!=8) break;				
				fristdb=0;
				///*************************can_wield,just_for
				if(strsrch(just_for,type)!=-1) continue;
				if(can_wield!=" ") mp[can_wield] = 1;
				if(is_prop==1){
					if(StrToFloat(add_num)!="FaileD"){
					add_num = StrToFloat(add_num);
					if(add_use==1) tempshuf = mp["weapon_prop"][add_type]+add_num;
					if(add_use==2) tempshuf = mp["weapon_prop"][add_type]-add_num;
					if(add_use==3) tempshuf = mp["weapon_prop"][add_type]*add_num;
					if(add_use==4) tempshuf = mp["weapon_prop"][add_type]/add_num;
					if(add_use==5) tempshuf = add_num;
					if(is_sure==0) tempshuf = tempshuf*c*(random(me->query("pur"))+31)/50;
					tempshud = to_int(tempshuf);
					mp["weapon_prop"][add_type] = tempshud;}
					else{
					tempshuf = add_num;
					mp["weapon_prop"][add_type]= (string)(tempshuf);
					}
				}
				else {
					if(StrToFloat(add_num)!="FaileD"){
					add_num = StrToFloat(add_num);
					if(add_use==1) tempshuf = mp[add_type]+add_num;
					if(add_use==2) tempshuf = mp[add_type]-add_num;
					if(add_use==3) tempshuf = mp[add_type]*add_num;
					if(add_use==4) tempshuf = mp[add_type]/add_num;
					if(add_use==5) tempshuf = add_num;
					if(is_sure==0) tempshuf = tempshuf*c*(random(me->query("pur"))+31)/50;
					tempshud = to_int(tempshuf);
					mp[add_type] = tempshud;}
					else{
					tempshuf = add_num;
					mp[add_type]= (string)(tempshuf);
					}
				}	
			}
	}
	if(debug_mode) tell_object(me,sprintf("经过附加属性修改的%d\n",mp["weapon_prop"]["damage"]));
		
	mp["weapon_prop"]["damage"] = to_int(mp["weapon_prop"]["damage"]*tick_count2*(80+random(41))/100);
	if(debug_mode) tell_object(me,sprintf("由随机平衡以后的%d\n",mp["weapon_prop"]["damage"]));
		
	//if( imbue_sta >	0 ){
		//special_weapon_status(imbue_sta,qua);
		//imbue_sta = 0;
	//}  /// xixi

	if( sizeof(special_st) > 0 ) {
		name = special_st[random(sizeof(special_st))];
	}
	else name = "";

	mp["name"] = name + mp["basic_name"] + mp["name"] + NOR;
	mp["name_st"] =	name_st;
	/*
	switch(qua) {
		case 1: j=(level-  0)*100/ 80; break; // 80
		case 2: j=(level- 80)*100/ 90; break; // 170
		case 3: j=(level-170)*100/100; break; // 270
		case 4: j=(level-270)*100/120; break; // 390
		case 5: j=(level-390)*100/ 10; break; // 400
	}
	if( j>100 ) j = 100;
*/
	//if(qua<5) mp["weapon_prop"]["damage"] = mp["weapon_prop"]["damage"]/2 + random(mp["weapon_prop"]["damage"]/2);
	//mp["weapon_prop"]["damage"] = mp["weapon_prop"]["damage"] * (100+j)/200;

	switch(type) {
		case "jintie":  i=1; break;
		case "shentie": i=2; break;
		case "xuantie": i=3; break;
		case "hantie": i=4; break;
		default: i=0; break;
	}
	if(i>0) {
		if(qua==4 && i>2) {
			//mp["weapon_prop"]["damage"] = mp["weapon_prop"]["damage"] * (10+i-2)/10;
			mp["rigidity"] += random((i-2)*3);
		}
		else if(qua<=3) {
			//mp["weapon_prop"]["damage"] = mp["weapon_prop"]["damage"] * (15+i)/15;
			mp["rigidity"] += random(i*2);
		}
	}
	
	if( mp["weapon_prop"]["damage"] > 200 && qua < 5 )
		mp["weapon_prop"]["damage"] = 200;

	if(!userp(me)) mp["maker"] = me->name(1) + "(" + capitalize(me->query("id")) + ")";
	else {
		mp["maker"] = worker_title(me,"duanzao");
		mp["maker"] += "  " + me->name(1) + "(" + capitalize(me->query("id")) + ")";
	}

	mp["save_id"] = sprintf("%s%dw",me->query("id"),time());

	return mp;
}

mapping* weapon_ranks;
mapping* armor_ranks;

void set_ranks(string type,mapping db)
{
	if(type=="weapon") weapon_ranks=copy(db);
	else if(type=="armor") armor_ranks=copy(db);
	else return;
	save();
}

int weapon_rank(object wp)
{
	int i, score;	
	mapping rank;
	int time;

	if( !wp ) return -1;
	score = wp->query("weapon_prop/damage");
	rank = wp->query("weapon_prop");
	if (mapp(rank)) {
		foreach (string item in keys(rank)) {
			switch (item) {
				case "damage": i = rank["damage"]; break;
				case "dexerity": i = 1300; break;
				case "strength": i = 1300; break;
				case "constitution": i = 1300; break;
				case "intelligence": i = 1500; break;
				case "qi": i = 8; break;
				case "jing": i = 5; break;
				case "jingli": i = 5; break;
				case "neili": i = 8; break;
				case "attack": i = 200; break;
				case "dodge": i = 150; break;
				case "parry": i = 150; break;
				default: i = 100; break;
			}
			if (intp(rank[item]))
				score += ( ABS(rank[item]) * i / 100 );
			score += 10;
		}
	}

	score += wp->query("rigidity") * 7;
	score += wp->query("sharpness") * 8;
	score = score * (wp->query("poison_number")?6:5) / 5;
	if (wp->query("weapon_prop/score")){
       score = wp->query("weapon_prop/score");
       }
	if( wp->query("imbued")<2 ) return score;
		
	if (!sizeof(weapon_ranks)) restore();
	if (!sizeof(weapon_ranks)) weapon_ranks = ({ });
	
	//一个礼拜不登陆即删除
	for (i = 0; i < sizeof(weapon_ranks); i++)
		if(time()-weapon_ranks[i]["time"]>NO_LOGIN_D*86400)
		{
			BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,"DELETE FROM mud_obj WHERE id='"+weapon_ranks[i]["save_id"]+"' AND type='weapon' AND site='"+INTERMUD_MUD_NAME+"'");
			weapon_ranks = weapon_ranks[0..i-1] + weapon_ranks[i+1..<1];			
			i--;
		}
	
	for (i = 0; i < sizeof(weapon_ranks); i++)
		//如果已经在列表里检查score是否有变动
                if(wp->query("save_id")==weapon_ranks[i]["save_id"]){
                	if(score==weapon_ranks[i]["score"]
                	&& wp->query("owner")==weapon_ranks[i]["owner"]
                	&& wp->query("name")==weapon_ranks[i]["name"]
                	&& wp->query("id")==weapon_ranks[i]["id"]
                	){
                		weapon_ranks[i]["time"] = time();
                		return score;
                	}
                	weapon_ranks[i]["score"] = score;
                	weapon_ranks[i]["owner"] = wp->query("owner");
                	weapon_ranks[i]["name"] = wp->query("name");
                	weapon_ranks[i]["id"] = wp->query("id");
                	sscanf(wp->query("weapon_mp/save_id"),"%*s%d",time);
			BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,sprintf("UPDATE mud_obj SET type='weapon',level='%d',score='%d',time='%d',utime='%d',details='%s',site='%s',name='%s' WHERE id='%s'",
			wp->query("imbued"),
			score,
			time,
			time(),
			(stringp(wp->query("name_st"))&&strlen(wp->query("name_st"))>3)?wp->query("name_st"):"",
			INTERMUD_MUD_NAME,
			wp->query("name")+"("+wp->query("id")+")",
			wp->query("weapon_mp/save_id")),0,"");
			return score;
                }
	//weapon_ranks = sort_array(weapon_ranks, (: sort_rank :));//重新排列
        for (i = 0; i < sizeof(weapon_ranks); i++)
                if(score > weapon_ranks[i]["score"]) break;
        if (i > RANK_TOTAL) return score;
        
        rank = ([       "save_id":      wp->query("save_id"),
        		"id":           wp->query("id"),
                        "name":         wp->query("name"),
                        "maker":        wp->query("maker"),
                        "owner":        wp->query("owner"),
                        "score":        score,
                        "time":         time() ]);
        if (!sizeof(weapon_ranks)) weapon_ranks = ({ rank });
        else weapon_ranks = weapon_ranks[0..i-1] + ({ rank }) + weapon_ranks[i..RANK_TOTAL];
        sscanf(wp->query("weapon_mp/save_id"),"%*s%d",time);	
        //maker,        
	BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,sprintf("REPLACE mud_obj(id,type,level,name,user,score,time,utime,details,site) VALUES('%s','weapon','%d','%s','%s','%d','%d','%d','%s','%s')",
	wp->query("weapon_mp/save_id"),
	//wp->query("maker"),
	wp->query("imbued"),
	wp->query("name")+"("+wp->query("id")+")",
	wp->query("maker"),
	score,
	time,
	time(),
	(stringp(wp->query("name_st"))&&strlen(wp->query("name_st"))>3)?wp->query("name_st"):"",
	INTERMUD_MUD_NAME ),0,"");
        save();
	return score;
}

int sort_rank(mapping rank1, mapping rank2)
{
        reset_eval_cost(); //add by snowman@SJ
        return rank2["score"]-rank1["score"];
}

void show_rank(object me,string type,int j)
{
	int i, u, flag;
	//int j = RANK_TOTAL;
	string msg;
        string str;
        //string *pattern = ({ "'.'", "" });
        //string *color1 = ({ "", BRED });
        //string *color2 = ({ "", NOR });
        mapping* ranks;
        //write(sprintf("%O\n",weapon_ranks));
        
        //me->start_more
        
        if(type=="weapon") ranks = weapon_ranks;
        else if(type=="armor") ranks = armor_ranks;
        else return;
        if(!arrayp(ranks) || sizeof(ranks)==0 ){
        	if(type=="weapon") write("目前江湖中没有任何锻造的兵器。\n");
		if(type=="armor") write("目前江湖中没有任何织造的防具。\n");
        	return;
        }
        ranks = sort_array(ranks, (: sort_rank :));
        str = "\n";
        if(type=="weapon") str += "                            ┏  书 剑 兵 器 排 行 榜  ┓\n";
        if(type=="armor")  str += "                            ┏  书 剑 防 具 排 行 榜  ┓\n";
        str += "┏━━┯━━━━━━━━━━┻━━━━━━┯━━━━━┻━━━━━━━━━┯━━━┓\n";
        str += sprintf("┃%|4s%36s%32s%|6s┃\n",
	"名次│",
	"       名              称       │",	
	"      制     造     者      │",
	"评价"
        );        
        str += "┠──┴─────────────────┴───────────────┴───┨\n";
        if (j < 1) j = 10;
        if (j > RANK_TOTAL) j = RANK_TOTAL;
        if (j > sizeof(ranks)) j = sizeof(ranks);        
        for (i = 0; i < j; i++) {
                if (i % 4 == 3) u = 0;
                else u = 1;
                if (i == j-1) u = 1;
                flag = (stringp(ranks[i]["owner"]) && ranks[i]["owner"]!="" && ranks[i]["owner"]!="0");
                if(flag) msg = sprintf(HIG"属%-8s私有"NOR,capitalize(ranks[i]["owner"]));
                //str += sprintf("┃%"+pattern[u]+"|4d%"+pattern[u]+"18s%"+pattern[u]+"-18s%"+pattern[u]+"|32s%"+pattern[u]+"|8d┃%s\n",
                str += sprintf("┃%|4d%|36s%|32s%|8d┃%s\n",
                                i+1,
                                ranks[i]["name"]+"("+capitalize(ranks[i]["id"])+")",
                                ranks[i]["maker"],
                                ranks[i]["score"],
                                flag?msg:"",
                                );
        }             
        str += "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n";
        me->start_more(str);
}

////////////////////////// make armor ////////////////////////////
object make_armor(object me,mixed type,int qua,string material,mapping shuxing,string* status)
{
	mapping	w_mp;
	object wp;
	string str = "", st;
	int w, p, new_w=0;
	object* clone;

	if( stringp(type) ) {
		if (type == TYPE_CLOTH)
			type = TYPE_COAT;
		w_mp = make_user_armor_random(me, type, qua, material,shuxing,status);
		if( !mapp(w_mp)	){
			write("Error! no w_mp! \n");
			return 0;
		}

		new_w = 1;
		special_st = name_st = ({ });
	}
	else if( mapp(type) ) {
		w_mp = type;
	}
	else return 0;
	
	str = w_mp["save_id"];
	clone = filter_array(children(USER_ARMOR), (: clonep :));
	for( w = 0;w<sizeof(clone); w++ ){
                if ( clone[w]->query("save_id") == str )
                        return 0;
        }
	str = "";
		
	if( stringp(w_mp["long2"]) && w_mp["long2"]!="" && w_mp["long2"]!="0" )
		str = w_mp["long2"];
	str += "这是由";
	switch(w_mp["material"]){
		case "longcansi": str += HIY"龙茧蚕丝"NOR;break;		
		case "tiancansi": str += WHT"天蚕丝"NOR; break;
		case "bingcansi": str += HIW"冰蚕丝"NOR; break;
		case "yucansi":   str += GRN"玉蚕丝"NOR; break;
		case "mumianhua": str += HIY"木棉花"NOR; break;
		case "cansi":     str += HIW"蚕丝"NOR; break;
		case "zhuma":     str += HIY"苎麻"NOR; break;
		case "dama":      str += YEL"大麻"NOR; break;
		case "yama":      str += YEL"亚麻"NOR; break;
		case "mianhua":   str += HIW"棉花"NOR; break;
		default: str +=	"布料";	break;
	}
	w = w_mp["weight"];
	str +=	"制成，重"+sprintf("%s", chinese_number(w/500)+"斤"+chinese_number((w%500)/50)+"两"+chinese_number((w%50)/5)+"钱")+"的"+w_mp["name"]+"。\n";

	if( new_w )
		p = w_mp["armor_prop"]["armor"];
	else if( intp(w_mp["armor_prop"]["armor"]) )
		p = w_mp["armor_prop"]["armor"];
	else p = 0;

	if( w_mp["imbued"] < 5 && p > 350 && !new_w ){
		delete_user_armor(me, w_mp["save_id"], "使用Bug致使威力过高");
		return 0;
	}
	//else if( p <= 0 && !new_w){
	//	delete_user_armor(me, w_mp["save_id"], "系统Bug致使毫无威力");
	//	return 0;
	//}
	/////这里注意下boot mantle
	if(w_mp["armor_type"]==TYPE_BOOTS||w_mp["armor_type"]==TYPE_SURCOAT) str += "看起来具有"+ armor_power(w_mp["armor_prop"],w_mp["armor_type"]) + "的闪避力！\n";
	else str += "看起来具有"+ armor_power(w_mp["armor_prop"],w_mp["armor_type"]) + "的防御力！\n";
	str += "装备要求：臂力【" +chinese_number(w_mp["wear_str"])+ "】，"
		+ "根骨【" +chinese_number(w_mp["wear_con"])+ "】，"
		+ "最大内力【" +chinese_number(w_mp["wear_maxneili"])+ "】\n";

	if( w_mp["name_st"] ) {
		if( stringp(w_mp["name_st"]) && strlen(w_mp["name_st"])>3 )
			str += "以及一排古篆字【 "HIG +	w_mp["name_st"]	+ NOR" 】\n";
		else if( arrayp(w_mp["name_st"]) && sizeof(w_mp["name_st"]) > 0 ) {
			st = implode(w_mp["name_st"][0..<1], "、");
			w_mp["name_st"] = st;
			str += "以及一排古篆字【 "HIG +	st + NOR" 】\n";
		}
	}

	if( stringp(w_mp["maker"]) )
		str += "隐约能看见防具制造者的姓名：" + w_mp["maker"] + "\n";
	
	if(stringp(w_mp["owner"]) && w_mp["owner"]!=""&& w_mp["owner"]!="0" && LOGIN_D->find_body(w_mp["owner"]) )
		str += "\n上面刻了几个小字："+LOGIN_D->find_body(w_mp["owner"])->query("name")+"("+capitalize(w_mp["owner"])+")\n";

	wp = new(USER_ARMOR);
	wp->set("armor_mp", copy(w_mp));
	wp->set("dur",w_mp["dur"]);

	if( wp->armor_setup(copy(w_mp)) ){
		wp->set("armor_mp/value" , armor_rank(wp)*8*100);
		wp->set("value" , wp->query("armor_mp/value") );
		wp->set("long" , str);
		if(w_mp["armor_type"]==TYPE_HEAD  || w_mp["armor_type"]==TYPE_ARMOR) wp->set("male_only",1);
		//if(w_mp["armor_type"]==TYPE_HANDS || w_mp["armor_type"]==TYPE_COAT) wp->set("female_only",1);
		if(w_mp["armor_type"]==TYPE_COAT) wp->set("female_only",1);
		
		if (wizardp(me)) wp->set_temp("apply/long",({wp->short()+"\n"+wp->query("long")+WORKER_D->get_msg(wp->query("armor_prop")) }));

		if( new_w && w_mp["imbued"]>2 ){
			// 记录格式：英文id：等级：中文名：类型：防御力：评价
			log_file("career/zhizao", sprintf("%-19s:%d:%-20s:%-6s:%-3d:%d\n",w_mp["save_id"],w_mp["imbued"],w_mp["name"],type,w_mp["armor_prop"]["armor"],armor_rank(wp)), me);
		}
		return wp;
	}
	else return 0;
}

protected mapping make_user_armor_random(object me,string type, int qua, string material,mapping shuxing,string* status)
{
	string wp_name,	name;
	string *types;
	int i,level,j;
	
	mixed add_num;
	mixed tempshuf;
	int tempshud;
	float c;
	string temp;
	int fristdb = 1;
	
	if( member_array(type, keys(ARMOR_MAP)) == -1 ) {
		write("Armor Type out of range. \n");
		return 0;
	}
	if( qua<1 || qua>5 ) {
		write("Armor qua out of range. \n");
		return 0;
	}

	mp = ARMOR_DEFAULT_SETTINGS;
	mp += copy(ARMOR_MAP[type]);
	
	if(debug_mode) tell_object(me,sprintf("最初的armor：%d dodge：%d\n",mp["armor_prop"]["armor"],mp["armor_prop"]["dodge"]));
		
	switch (qua) {
		case 5:
			mp += copy(ARMOR_SUPER_B);
			if(type=="boot" || type=="mantle") mp += ([ "armor_prop": (["dodge": mp["armor_prop"]["dodge"]+35 ]), ]);
			else mp += ([ "armor_prop": (["armor": mp["armor_prop"]["armor"]+35 ]), ]);
			i = random(sizeof(Armor_Super_Class));
			wp_name	= keys(Armor_Super_Class)[i];
			mp += Armor_Super_Class[wp_name];
			mp["id"] = ({ Armor_Super_Class[wp_name]["id"]+" "+type, Armor_Super_Class[wp_name]["id"], type });
			//mp += copy(ARMOR_SPECIAL_B);
			//i = random(sizeof(Armor_Special_Class[type]));
			//wp_name	= keys(Armor_Special_Class[type])[i];
			//mp += copy(Armor_Special_Class[type][wp_name]);
			//mp["id"] = ({ mp["id"] , type });
			break;
		case 4:
			mp += copy(ARMOR_SUPER_B);
			if(type=="boot" || type=="mantle") mp += ([ "armor_prop": (["dodge": mp["armor_prop"]["dodge"]+25 ]), ]);
			else mp += ([ "armor_prop": (["armor": mp["armor_prop"]["armor"]+25 ]), ]);
			i = random(sizeof(Armor_Super_Class));
			wp_name	= keys(Armor_Super_Class)[i];
			mp += Armor_Super_Class[wp_name];
			mp["id"] = ({ Armor_Super_Class[wp_name]["id"]+" "+type, Armor_Super_Class[wp_name]["id"], type });
			break;
		case 3:
			mp += copy(ARMOR_GREAT_B);
			if(type=="boot" || type=="mantle") mp += ([ "armor_prop": (["dodge": mp["armor_prop"]["dodge"]+15 ]), ]);
			else mp += ([ "armor_prop": (["armor": mp["armor_prop"]["armor"]+15 ]), ]);
			i = random(sizeof(Armor_Great_Class));
			wp_name	= keys(Armor_Great_Class)[i];
			mp["id"] = ({ Armor_Great_Class[wp_name]+" "+type, Armor_Great_Class[wp_name], type });
			break;
		case 2:
			mp += copy(ARMOR_GOOD_B);
			if(type=="boot" || type=="mantle") mp += ([ "armor_prop": (["dodge": mp["armor_prop"]["dodge"]+5 ]), ]);
			else mp += ([ "armor_prop": (["armor": mp["armor_prop"]["armor"]+5 ]), ]);
			wp_name	= Armor_G_3_class[random(sizeof(Armor_G_3_class))];
			mp["id"] = ({ "good "+type , type});
			break;
		case 1:
			if(type=="boot" || type=="mantle") mp += ([ "armor_prop": (["dodge": mp["armor_prop"]["dodge"]+1 ]), ]);
			else mp += ([ "armor_prop": (["armor": mp["armor_prop"]["armor"]+1 ]), ]);
			wp_name	= mp["basic_name"];
			mp["id"] = ({ "normal "+type , type});
			break;
	}
	if(debug_mode) tell_object(me,sprintf("默认的armor：%d dodge：%d\n",mp["armor_prop"]["armor"],mp["armor_prop"]["dodge"]));
	mp["basic_name"] = wp_name;
	mp["material"] = material;
	if( qua > 3 ) mp["utime"] = time();
	mp["dur"] = mp["max_dur"];

	mp["weight"] = mp["weight"]*2/3 + random(mp["weight"]*2/3);
	mp["wear_maxneili"] = mp["wear_maxneili"]*2/3 + random(mp["wear_maxneili"]*2/3);
	mp["wear_con"] = mp["wear_con"]*2/3 + random(mp["wear_con"]*2/3);
	mp["wear_str"] = mp["wear_str"]*2/3 + random(mp["wear_str"]*2/3);
	
	/*
	k = 0;
	j = qua;
	j = status;
	while(j--) {
		i = special_armor_status(0,qua,type);
		if(i==3) break;
		if(i==2) { if(k==1) break; else k=1; }
	}
	*/	
	level = me->query_skill("zhizao",1);
	if(level<220) c = 0.002272*level;
	else if(level<400) c= 0.5+0.002778*(level-220);
	//if(level<600)
	else c= 1 + 0.005*(level-400);
	if(c>2) c = 2;//限制到600 level xixi
		
	if(type=="boot" || type=="mantle") mp["armor_prop"]["dodge"] += to_int(15*c);	
	else mp["armor_prop"]["armor"] += to_int(15*c);
	if(debug_mode) tell_object(me,sprintf("由铁匠技能改变的的armor：%d dodge：%d\n",mp["armor_prop"]["armor"],mp["armor_prop"]["dodge"]));
	
	if(mapp(shuxing)){
		types = keys(shuxing);
		if(sizeof(types)>0) {for(i=0;i<sizeof(types);i++) mp["armor_prop"][types[i]] += to_int(shuxing[types[i]]*c*(random(me->query_kar())+91)/100) ;}
	}
	if(type=="boot" || type=="mantle")
	{
		mp["armor_prop"]["dodge"] += mp["armor_prop"]["armor"];		
		map_delete(mp["armor_prop"],"armor");
	}
	if(debug_mode) tell_object(me,sprintf("加入玉的影响的armor：%d dodge：%d\n",mp["armor_prop"]["armor"],mp["armor_prop"]["dodge"]));
	
	j = sizeof(status);
	while(j--)
	{
		temp = status[j];
                fristdb=1;
 		        if(sscanf(temp,"status_type%dspe_name%sjade_show%sitem_show%sis_prop%dis_sure%dadd_type%sadd_use%dadd_num%scan_wield%sjust_for%ssta_over%s",
				status_type,spe_name,jade_show,item_show,is_prop,is_sure,add_type,add_use,add_num,can_wield,just_for,temp)==12)
			while( (fristdb==1 || temp!=" ") && spe_name!=" "){				
				if(fristdb==1){
					special_st +=({ spe_name });
					name_st	+=({ item_show });}
				if(fristdb==0) if(sscanf(temp," next_add_ is_prop%dis_sure%dadd_type%sadd_use%dadd_num%scan_wield%sjust_for%ssta_over%s",
						is_prop,is_sure,add_type,add_use,add_num,can_wield,just_for,temp)!=8) break;				
				fristdb=0;
				///*************************can_wield,just_for
				if(strsrch(just_for,type)!=-1) continue;
				if(can_wield!=" ") mp[can_wield] = 1;
				if(is_prop==1){
					if(StrToFloat(add_num)!="FaileD"){
					add_num = StrToFloat(add_num);
					if(add_use==1) tempshuf = mp["armor_prop"][add_type]+add_num;
					if(add_use==2) tempshuf = mp["armor_prop"][add_type]-add_num;
					if(add_use==3) tempshuf = mp["armor_prop"][add_type]*add_num;
					if(add_use==4) tempshuf = mp["armor_prop"][add_type]/add_num;
					if(add_use==5) tempshuf = add_num;
					if(is_sure==0) tempshuf = tempshuf*c*(random(me->query("pur"))+31)/50;
					tempshud = to_int(tempshuf);
					mp["armor_prop"][add_type] = tempshud;}
					else{
					tempshuf = add_num;
					mp["weapon_prop"][add_type]= (string)(tempshuf);
					}
				}
				else {
					if(StrToFloat(add_num)!="FaileD"){
					add_num = StrToFloat(add_num);
					if(add_use==1) tempshuf = mp[add_type]+add_num;
					if(add_use==2) tempshuf = mp[add_type]-add_num;
					if(add_use==3) tempshuf = mp[add_type]*add_num;
					if(add_use==4) tempshuf = mp[add_type]/add_num;
					if(add_use==5) tempshuf = add_num;
					if(is_sure==0) tempshuf = tempshuf*c*(random(me->query("pur"))+31)/50;
					tempshud = to_int(tempshuf);
					mp[add_type] = tempshud;}
					else{
					tempshuf = add_num;
					mp[add_type]= (string)(tempshuf);
					}
				}
			}
	}
	if(debug_mode) tell_object(me,sprintf("经过附加属性的修改的armor：%d dodge：%d\n",mp["armor_prop"]["armor"],mp["armor_prop"]["dodge"]));	
			
	mp["armor_prop"]["armor"] = to_int(mp["armor_prop"]["armor"]*tick_count2*(80+random(41))/100)*10/armor_modify[type];
	if(type=="boot"||type=="mantle")
		mp["armor_prop"]["dodge"] = to_int(mp["armor_prop"]["dodge"]*tick_count2*(80+random(41))/200)*10/armor_modify[type];
	if(debug_mode) tell_object(me,sprintf("经过随机平衡系数调整的armor：%d dodge：%d\n",mp["armor_prop"]["armor"],mp["armor_prop"]["dodge"]));
	if( sizeof(special_st) > 0 ) {
		name = special_st[random(sizeof(special_st))];
	}
	else name = "";

	//if(qua<5)
	//	mp["name"] = name + mp["basic_name"] + mp["name"] + NOR;
	//else	
		//mp["name"] = name + mp["basic_name"];
	mp["name"] = name + mp["basic_name"] + mp["name"] + NOR;
	mp["name_st"] =	name_st;
	/*
	switch(qua) {
		case 1: j=(level-  0)*100/ 80; break; // 80
		case 2: j=(level- 80)*100/ 90; break; // 170
		case 3: j=(level-170)*100/100; break; // 270
		case 4: j=(level-270)*100/120; break; // 390
		case 5: j=(level-390)*100/ 10; break; // 400
	}
	if( j>100 ) j = 100;
	if(qua<5) mp["armor_prop"]["armor"] = mp["armor_prop"]["armor"]/2 + random(mp["armor_prop"]["armor"]/2);
	mp["armor_prop"]["armor"] = mp["armor_prop"]["armor"] * (100+j)/200;
	*/

	switch(type) {
		case "yucansi":   i=1; break;
		case "bingcansi": i=2; break;
		case "tiancansi": i=3; break;
		case "longcansi": i=4; break;
		default: i=0; break;
	}
	if(i>0) {
		if(qua==4 && i>2) {
			if(type=="boot" || type=="mantle") mp["armor_prop"]["dodge"] *= ((10+i-2)/10);
			else mp["armor_prop"]["armor"] *= ((10+i-2)/10);
		}
		else if(qua<3) {
			if(type=="boot" || type=="mantle") mp["armor_prop"]["dodge"] *= ((10+i)/10);
			mp["armor_prop"]["armor"] *= ((10+i)/10);
		}
	}
	if(debug_mode) tell_object(me,sprintf("经过质地影响调整的armor：%d dodge：%d\n",mp["armor_prop"]["armor"],mp["armor_prop"]["dodge"]));
	//if(type=="boot" || type=="mantle")
	//{
	//	mp["armor_prop"]["dodge"] += mp["armor_prop"]["armor"];		
	//	map_delete(mp["armor_prop"],"armor");
	//}
	if( mp["armor_prop"]["armor"] > 130 && qua < 5 )
		mp["armor_prop"]["armor"] = 130;

	if(!userp(me)) mp["maker"] = me->name(1) + "(" + capitalize(me->query("id")) + ")";
	else
	{
		mp["maker"] = worker_title(me, "zhizao");
		mp["maker"] += "  " + me->name(1) + "(" + capitalize(me->query("id")) + ")";
	}

	mp["save_id"] = sprintf("%s%da",me->query("id"),time());
	return mp;
}

int armor_rank(object wp)
{
	int i, score;
	mapping rank;
	int time;

	if( !wp ) return -1;
	score = wp->query("armor_prop/armor");
	rank = wp->query("armor_prop");
	if (mapp(rank)) {
		foreach (string item in keys(rank)) {
			switch (item) {
				case "armor": i = 100; break;
				case "dexerity": i = 1300; break;
				case "strength": i = 1300; break;
				case "constitution": i = 1300; break;
				case "intelligence": i = 1500; break;
				case "qi": i = 10; break;
				case "jing": i = 7; break;
				case "jingli": i = 7; break;
				case "neili": i = 10; break;
				case "dodge": i = 160; break;
				case "parry": i = 160; break;
				case "antipoison": i = 120; break;
				}
			if (intp(rank[item]))
				score += ( ABS(rank[item]) * i / 100 );
			score += 10;
		}
	}

	score += wp->query("storeneili") / 80;
	if (wp->query("storetimes")) score += ( (300 - wp->query("storetimes")) / 3 );
	score += wp->query("decdamage") * 4;
	
	if( wp->query("imbued")<2 ) return score;
	
	if (!sizeof(armor_ranks)) restore();
	if (!sizeof(armor_ranks)) armor_ranks = ({ });

	for (i = 0; i < sizeof(armor_ranks); i++)
		if(time()-armor_ranks[i]["time"]>NO_LOGIN_D*86400)
		{
			BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,"DELETE FROM mud_obj WHERE id='"+armor_ranks[i]["save_id"]+"' AND type='armor' AND site='"+INTERMUD_MUD_NAME+"'");
			armor_ranks = armor_ranks[0..i-1] + armor_ranks[i+1..<1];			
			i--;
		}
	        
	for (i = 0; i < sizeof(armor_ranks); i++)
                if(wp->query("save_id")==armor_ranks[i]["save_id"]){
                	if(score==armor_ranks[i]["score"]
                	&& wp->query("owner")==armor_ranks[i]["owner"]
                	&& wp->query("name")==armor_ranks[i]["name"]
                	&& wp->query("id")==armor_ranks[i]["id"]
                	){
                		armor_ranks[i]["time"] = time();//when login refresh time
                		return score;
                	}
                	armor_ranks[i]["score"] = score;
                	armor_ranks[i]["owner"] = wp->query("owner");
                	armor_ranks[i]["name"] = wp->query("name");
                	armor_ranks[i]["id"] = wp->query("id");
                	sscanf(wp->query("armor_mp/save_id"),"%*s%d",time);
			BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,sprintf("UPDATE mud_obj SET type='armor',level='%d',score='%d',time='%d',utime='%d',details='%s',site='%s',name='%s' WHERE id='%s'",
			wp->query("imbued"),
			score,
			time,
			time(),
			(stringp(wp->query("name_st"))&&strlen(wp->query("name_st"))>3)?wp->query("name_st"):"",
			INTERMUD_MUD_NAME,
			wp->query("name")+"("+wp->query("id")+")",
			wp->query("armor_mp/save_id") ),0,"");                	
                       	return score;
                }
	//armor_ranks = sort_array(armor_ranks, (: sort_rank :));//重新排列
        for (i = 0; i < sizeof(armor_ranks); i++)
                if(score > armor_ranks[i]["score"]) break;
        if (i > RANK_TOTAL) return score;
                
        rank = ([       "save_id":      wp->query("save_id"),
        		"id":           wp->query("id"),
                        "name":         wp->query("name"),
                        "maker":        wp->query("maker"),
                        "owner":        wp->query("owner"),
                        "score":        score,
                        "time":         time() ]);
        if (!sizeof(armor_ranks)) armor_ranks = ({ rank });
        else armor_ranks = armor_ranks[0..i-1] + ({ rank }) + armor_ranks[i..RANK_TOTAL];
        sscanf(wp->query("armor_mp/save_id"),"%*s%d",time);	
        //maker,        
	BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,sprintf("REPLACE mud_obj(id,type,level,name,user,score,time,utime,details,site) VALUES('%s','armor','%d','%s','%s','%d','%d','%d','%s','%s')",
	wp->query("armor_mp/save_id"),
	//wp->query("maker"),
	wp->query("imbued"),
	wp->query("name")+"("+wp->query("id")+")",
	wp->query("maker"),
	score,
	time,
	time(),
	(stringp(wp->query("name_st"))&&strlen(wp->query("name_st"))>3)?wp->query("name_st"):"",
	INTERMUD_MUD_NAME ),0,"");
        save();
	return score;
	//return score;
}

//////////////////////////// make drug ////////////////////////
void set_drug_busy(object me,int busy)
{
	call_out("clear_drug_busy",busy,me);
}

protected void clear_drug_busy(object me)
{
	if(!me) return;
	me->clear_condition("medicine");
}

void set_drug_work(object me,int busy)
{
	call_out("clear_drug_work",busy,me);
}

protected void clear_drug_work(object me)
{
	mapping mp;
	string * mpk;
	int * mpv;
	int i;

	if( !me || !mapp(me->query_temp("drug_apply")) ) return;
	mp = me->query_temp("drug_apply");
	mpk = keys(mp);
	mpv = values(mp);

	for(i=0;i<sizeof(mp);i++) {
		if( mpk[i] == "name" ) continue;
		me->add_temp("apply/"+mpk[i],-mpv[i]);
	}

	tell_object(me,"你服用的"+mp["name"]+NOR"的药力消退了。\n");
	me->delete_temp("drug_apply");
}

/////////////////////////////// create ////////////////////////

void create()
{
	seteuid(getuid());
	restore();
}

int remove()
{
	return 1;
}

int clean_all()
{
	return remove();
}

/////////////////////////modify///////////////////////////
object mater_random(object me,int type,int level)
{
//// type 是表示哪种材料 1 是 矿石  2 是布匹 3..... 3 玉石 4 zongzi(不可能从游戏中buy到的) 5book
///// level 表示等级 ...
//这里增加得到打造书的可能
	object mater;
	int n,d,lvl,randnum;	
	int i = 1;
	int* forbit = ({0,40,80,120,170,220,270,330,390,450,500});
	//int random_get = 0;
	
	if(!me) return 0;
	if(!type|| level == 0){
			if(!(random(200)==100)) return 0;
			type = random(3)? (random(2)?1:2):4;
			if(random(100)<5){
				type = 3;
				if(random(100)<5) type = 5;
			}//应该比较高了 先试试
		}
	//setup some var about type
	if(type==1) lvl = me->query_skill("caikuang",1);
	else if(type==2) lvl = me->query_skill("nongsang",1);
	else if(type==4) lvl = me->query_skill("nongsang",1);
	else lvl = me->query_kar()*(5+random(10));
	/////// some more ...
	if(!level || level == 0)
	{		
		d = lvl / 4;
		n = random(MATERIAL_LEVEL)+1;
		if(n<1) n = 1;
		while(forbit[n-1] > lvl)
		{
			n--;
		}//限制
        	randnum = random(sum(n,d));
        	if (sum(6,d) < randnum)
        	{ 
                	i = 7;
                	while (sum(i,d) < randnum)
                        	i++;
        	}        	
        	else {
                	while (sum(i,d) < randnum)
                        	i++;
        	}
        	level = i -1;
        	if(random(me->query_kar())==0) level++;
        	if(level > MATERIAL_LEVEL ) level = MATERIAL_LEVEL-1;
        	if(level==0) level=1;
	}
	if(type==3) {
		level += 2;
        	level = level / 2;
        	if(level>6 || level<1) level = 1;
        }
        else if(type==5)
        {
        	level = random(2)+1;
        }
	if(!level || level == 0) return 0;
	switch(type){
		case 1:mater = new(OBJ_DIR+"kuangshi");break;
		case 2:mater = new(OBJ_DIR+"buliao");break;
		case 3:mater = new(OBJ_DIR+"othermaterial");break;//已经限制level hehe
		case 4:mater = new(OBJ_DIR+"zhongzi");break;
		case 5:mater = new(OBJ_DIR+"book");break;
		default:return 0;
	}
	if(!mater) return 0;
	if(mater->set_level(level)){
		mater->set("owner",getuid(me));
		return mater;
	}
	if(mater) destruct(mater);
	return 0;
	//if(random_get==1) call_out("delay_channel", 1, "rumor", me->query("name")+"弄到了一"+mater->query("unit")+mater->name());	
}

string get_msg(mapping rank)
{	
	string str ="";
	string use,use2;
	
	if(!mapp(rank) || sizeof(keys(rank))<=0) return str;
	str += "它的功能有："+HIG"【";
	foreach (string item in keys(rank)) {
		use = "";
		use2 ="";
		switch(item){		
			case "damage":                use="伤害力";break;
			case "armor":                 use="防御力";break;
			case "strength":              use="力量";break;
			case "constitution":          use="根骨";break;
			case "dexerity":              use="身法";break;
			case "intelligence":          use="悟性";break;
			case "attack":		      use="命中";break;
			case "defense":               use="闪避";break;
			case "neili":                 use="内力";break;
			case "jingli":                use="精力";break;
			case "jing":                  use="精血";break;
			case "qi":                    use="气血";break;
			case "re_qi":                 use="气血恢复速度";use2="%";break;
			case "re_neili":              use="内力恢复速度";use2="%";break;
			case "re_jing":               use="精血恢复速度";use2="%";break;
			case "re_jingli":             use="精力恢复速度";use2="%";break;
			case "parry":                 use="招架";break;
			case "dodge":                 use="轻功";break;
			case "force":                 use="内功";break;
			case "armor_vs_force":        use="内功抗性";break;
			default:use="";
		}
		if(stringp(use) &&use!="" && intp(rank[item]) && rank[item]!=0 )
			str +="，"+use+"＋"+sprintf("%d",rank[item])+use2;
	}
	str += "】\n"NOR;
	str = replace_string(str,"【，","【");
	if(strsrch(str,"【】")!=-1) str ="";
	if(rank["karma"]!=0)       str =HIG"看上去闪闪发亮似乎有某种神奇的力量。\n"NOR+str;
	if(rank["personality"]!=0) str =HIM"据说，苏州的美女最喜欢这东西了。\n"NOR+str;
	return str;
}
mapping map_add(mapping old,mixed rank)
{
	int i;
	string* vebs;
	if(!mapp(old)) return 0;
	if(nullp(rank)) return old;
	if(floatp(rank)){
		vebs = keys(old);
		if(sizeof(vebs)==0) return old;
		for(i=0;i<sizeof(vebs);i++){
			old[vebs[i]] = to_int(old[vebs[i]] * rank);
			if(old[vebs[i]]<=0) map_delete(old,vebs[i]);
		}
		return old;
	}
	if(!mapp(rank)) return old;
	vebs = keys(rank);
	if(sizeof(vebs)==0) return old;
	for(i=0;i<sizeof(vebs);i++){
		old[vebs[i]] += rank[vebs[i]];
		if(old[vebs[i]]<=0) map_delete(old,vebs[i]);
	}
	if(!mapp(old)) return 0;
	return old;
}
float updown(object me,string type)
{
	float ud = 1.00;
	string party;
	//这些最好玩家自己体会 如果体会不出来就smash他	
	if(!me) return ud;
	if(!stringp(type)) return ud;
        if(mapp(me->query("family")) && stringp(me->query("family/family_name"))) party = me->query("family/family_name");
        if(stringp(party)){
        	if( ( party=="华山派" )  && type=="sword")    ud = 1.25;
        	if( ( party=="华山派" )  && type=="caikuang")    ud = 0.70;
        	if( ( party=="大轮寺" )  && type=="hammer")   ud = 1.25;
        	if( ( party=="丐帮" )    && type=="stick")    ud = 1.25;
        	if( ( party=="明教" )    && type=="dagger")   ud = 1.25;
        	if( ( party=="桃花岛" )  && type=="xiao")     ud = 1.25;
        	if( ( party=="嵩山派" )  && type=="sword") ud = 0.70;
        	if( ( party=="嵩山派" )  && type=="caikuang") ud = 1.30;
        	if( ( party=="少林派" )  && type=="nongsang") ud = 1.30;
        	if( ( party=="峨嵋派" )  && type=="coat")    ud = 1.25;
        	if( ( party=="铁掌帮" )  && type=="armor")    ud = 1.25;        	
        	if( ( party=="天龙寺" )  && type=="boot")     ud = 1.25;        	
        	if( ( party=="昆仑派" )  && type=="cap")      ud = 1.25;
        	if( ( party=="古墓派" )  && type=="glove")    ud = 1.25;
        	if( ( party=="姑苏慕容" )&& type=="belt")     ud = 1.25;
        	if( ( party=="姑苏慕容" )&& type=="nongsang")     ud = 0.70;
        	if( ( party=="星宿派" )  && type=="mantle")   ud = 1.25;
        	//////////
        	if( ( party=="神龙教" )  && type=="caiyao")   ud = 1.30;
        	if( ( party=="天龙寺" )  && type=="caiyao")     ud = 0.70;        	
        	if( ( party=="武当派" )  && type=="liandan")  ud = 1.30;        	
        	if( ( party=="铁掌帮" )  && type=="liandan")    ud = 0.70;
        }
        return ud;
        //PS: 既然有Up 当然也得有down ^_^
}
void get_status(object ob,int type,int level,int super,string use_type)
{
	string *types;
	int i,j,k,score_b;
	int score = 0;
	int t;
	string temp;
	string* spe_names = allocate(6);
	int* status_types = allocate(6);
	
	//status_types=({0,});
	if(!ob ||!level ||!type ||type>3 ||type<1) return;
	if(type==1 || type==2) return;///禁止原材料获得附加属性
		
	while(level--)
	{
		t=0;
		if(use_type=="weapon") i = status_weapon_lists(0,t);
		else if(use_type=="armor") i=status_armor_lists(0,t);
		else return;
		if(status_type!=0 && member_array(status_type,status_types)!=-1) continue;
		if(spe_name!=" " && member_array(spe_name,spe_names)!=-1) continue;
		if(spe_name!=" ") spe_names[level] = copy(spe_name);
		if(status_type!=0) status_types[level] = copy(status_type);
		if(StrToFloat(add_numa)!="FaileD") add_numa = FloatToStr(StrToFloat(add_numa)+random(add_numb));
		temp = sprintf("status_type%dspe_name%sjade_show%sitem_show%sis_prop%dis_sure%dadd_type%sadd_use%dadd_num%scan_wield%sjust_for%ssta_over ",
		status_type,spe_name,jade_show,item_show,is_prop,is_sure,add_type,add_use,add_numa,can_wield,just_for);
		while(if_next){
			t++;
			if(use_type=="weapon") status_weapon_lists(i,t);
			else if(use_type=="armor") status_armor_lists(i,t);
			else return;
			if(StrToFloat(add_numa)!="FaileD") add_numa = FloatToStr(StrToFloat(add_numa)+random(add_numb));
			temp += sprintf("next_add_ is_prop%dis_sure%dadd_type%sadd_use%dadd_num%scan_wield%sjust_for%ssta_over ",
			is_prop,is_sure,add_type,add_use,add_numa,can_wield,just_for);
		}
		ob->set("material_props/"+level,temp);
	}
	//考虑ing
	if(super==1){
	if(type==3) level = level*2;
	level = level*2000;
	types = keys(Status_list);
	while((super||random(level)>random(level/2)) && level-score>500)
	{		
		i = random(sizeof(types));
		score_b = 5000*Status_list[types[i]];
		for(j = 5000;score+score_b>level;j=j/2-random(j/2-1) ){
			k++;
			if(j>0) score_b = j*Status_list[types[i]];
			else break;
		}		
		if(j>0){
			ob->add("material_prop/"+types[i],j);
			score += score_b;
		}
	}}
	if(spe_name!=" ") ob->set("name",spe_name+ob->query("name"));
	ob->add("value",score);//价值体现	
	return;
}
/*
标准更换
	me->improve_skill("caikuang", improve*6);
	------------------>	
	WORKER_D->check_impove(me,"caikuang",improve*6,2);
modify 这里函数返回实际增加的点数
*/
int check_impove(object me,string skill,int improve,int flag)
{
	int level;	
	
	if(!userp(me)) return 0;
	level = me->query_skill(skill,1);
	switch(flag)
	{
		case 1:
			if(level>=50) return 0;
			break;
		case 2:
			if(level>=220) return 0;
			break;
		case 3:
			if(level<150 || level>=600) return 0;
			if(level>=450) improve = improve/4;
			else if(level>=400) improve = improve*2/4;
			else if(level>=350) improve = improve*3/4;
			break;		
		default:return 0;
	}	
	// about 七窍玲珑	
	if(level>=150 && level%10==0 ){
		mapping learned = me->query_learned();		
		if(learned[skill]+improve>=(level+1)*(level+1))
		{
			improve = (level+1)*(level+1)-learned[skill];
		}
		//在七窍玲珑系统中中应当设置该skills 离红只有1点尾数时可以进步 :)
		//就是 等于(level+1)*(level+1)-1 时  该skills便是可进步的
	}
	if(improve>0) me->improve_skill(skill,improve);
	return improve;
}
string query_save_file()
{
	return WORKER_FILE+"rank";
}

/*
int save()
{
	write("workerd saved. \n");
	return ::save();
}*/

void set_debug_mode() { debug_mode = 1; }
void unset_debug_mode() { debug_mode = 0; }
int querydebug() {return debug_mode;}
void set_tick_count(string tick) {sscanf(tick,"%f",tick_count2);} 
float query_tick_count() { return tick_count2; }

int check_item(object wp, object src, object dest)
{
	string user;
	int btime, ltime, t;

	if (!wp || wp->query("broken") || src == dest) return 1;
	if (wp->query("imbued") < 4) return 0;	// 高级装备才有这个限制
	
	return 0;//去掉限制
			
	t = time();
	// 离开身体
	if (!wp->query("ltime")) wp->set("ltime", t-39*86400);
	user = wp->query("user");	// 装备的持有人
	ltime = wp->query("ltime");	// 装备的上次维护时间
	if (src && userp(src)) {
		if (sscanf(wp->query("save_id"), src->query("id")+"%d", btime)
		 && btime > src->query("birthday")) {	// 判断是否为制造者
			if (user && dest && t - ltime >= 30*86400)
			if (!userp(dest) || dest->query("id") != user) {	// 离开制造者，但是没有还给持有者
				src->skill_death_penalty();
				message_vision("$N所有技能被降了半级。\n", src);
				log_file("career/maint", sprintf("src=%s,dest=%O,user=%s", src->query("id"), dest, user), src);//->query("id")
			}
		 	ltime = wp->set("ltime", t);	// 装备离开制造者重新开始计时
		}
	}
	if (dest && userp(dest)) {
		t -= ltime;
		if (sscanf(wp->query("save_id"), dest->query("id")+"%d", btime)
		 && btime > dest->query("birthday")) {	// 判断是否为制造者
			if (src && userp(src) && t >= 30*86400) {
				wp->set("user", src->query("id"));
				message_vision(wp->name()+"发出一种细不可闻的声音。\n", src, dest);
			}
		} else {
			wp->set("user", dest->query("id"));
			if(strsrch(wp->query("save_id"),"weilan tiejiang")!=-1) return 0;//zhujian shi打造不受此限制
			if (!src) {
				if (t >= 40*86400) {
					call_out("delay_channel", 1, "rumor", dest->query("name")+"身上的"+wp->name()+"因为太久没有维护而彻底损坏了。");
					call_out("delay_remind", 1, dest, "你身上的"+wp->name()+"因为太久没有维护而彻底损坏了。\n");
					destruct(wp);
					return 1;
				}
			}
			if (t >= 30*86400) {
				call_out("delay_remind", 1, dest, "你身上的"+wp->name()+"似乎有些异样，快拿去给制造者看看吧。\n");
			}
		}
	} else {
		wp->delete("user");
	}
	return 0;
}

void delay_channel(string channel, string arg)
{
	CHANNEL_D->do_channel(this_object(), channel, arg);
}

void delay_remind(object ob, string arg)
{
	if (ob) tell_object(ob, arg);
}
