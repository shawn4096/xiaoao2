// gf_wanted.c For GuanFu jobs.
// By snowman@SJ 10/06/2000

#include <ansi.h>
#include <guanfu.h>

mapping wanted;
mapping query_wanted() { return wanted; }
string *query_wanted_list() { return keys(wanted); }
void del_wanted(string id);
int query_wanted_size() { return sizeof(wanted); }
string wanted_list = "\n目前治安良好，官府无任何通缉文书贴出。\n\n";
private int do_wanted(object ob, mixed info);

int clear_wanted_list()
{
	wanted = ([]);
	wanted_list = "\n目前治安良好，官府无任何通缉文书贴出。\n\n";
	return 1;
}

string look_wanted(){	return wanted_list; }

void modify_list(int search)
{
	string *key, str = "\n";
      	int i, size;
      	object *obs;
		
	if( search ){
		clear_wanted_list();
		obs = filter_array(children(WANTED_NPC), (: clonep :));
		i = sizeof(obs);
		if( i && i > 0 ){
			while(i--){
				if( !environment(obs[i]) )
					destruct(obs[i]);
				else do_wanted(obs[i], obs[i]->query("gf_wanted_info"));
			}
		}
	}
	
      	key = query_wanted_list();
      	size = query_wanted_size();
      	if ( !size ){
      		wanted_list = "\n目前治安良好，官府无任何通缉文书贴出。\n\n";
		return;
	}
	
      	for( i = 0; i < size; i++ ){
      		str += sprintf("    %-30s，武功%-8s，赏金%s\n", wanted[key[i]]["name"]+"("+capitalize(key[i])+")", wanted[key[i]]["level"], MONEY_D->money_str(wanted[key[i]]["reward"]*50));
      	}
      	str += "\n揭榜请用 jie <通缉犯id> 的格式。\n";
    	wanted_list = "本府现通缉以下罪犯："+str+"\n\n";
    	return;
}

void del_wanted(string id)
{
	map_delete(wanted, id);
	modify_list(0);
}





void do_give_reward(string id, mapping target, object me, int dead)
{
	int exp, pot, i,level;
	string *pinji = ({ "一品领侍卫内大臣", "正二品九门提督","二品正黄旗都统","从二品正黄旗副都统","三品刑部副将","四品刑部参将","五品刑部统领","六品刑部游击", "七品刑部都司", "八品刑部守备", "九品巡捕营千总","扬州府巡捕营把总","扬州府巡捕头","扬州府巡捕" });
	
	if( !stringp(id) || !mapp(target) || !objectp(me) ) return;
	if( id == target["id"] ) {
		exp = target["reward"];
		if ( target["exp"] ) {
			i = me->query("combat_exp", 1)/ target["exp"];
			if ( i > 3 ) i = 4;
			if ( i < 1 ) i = 1;
		}
		else i = 1;
		exp /= i;
		if ( dead && target["action"] != "就地格杀" ){
			exp /= 2+random(3);
			pot = exp/4;
		}
		
		else {
			me->add("job_time/官府", 1);
			pot = exp/3;
			tell_object(me, "你为官府效命的次数增加了，目前已达到"+chinese_number(me->query("job_time/官府"))+"次。\n");
		}
		
		
		
		level=13;
				
		if (me->query("job_time/官府")>=10) level=12;
		if (me->query("job_time/官府")>=100) level=11;
		if (me->query("job_time/官府")>=500) level=10;
		if (me->query("job_time/官府")>=1000) level=9;
		if (me->query("job_time/官府")>=5000) level=8;
		if (me->query("job_time/官府")>=10000) level=7;
		if (me->query("job_time/官府")>=20000) level=6;
		if (me->query("job_time/官府")>=40000) level=5;
		if (me->query("job_time/官府")>=80000) level=4;
		if (me->query("job_time/官府")>=100000) level=3;
		if (me->query("job_time/官府")>=200000) level=2;
		if (me->query("job_time/官府")>=400000) level=1;
		if (me->query("job_time/官府")>=1000000) level=0;
		
		
		me->set("title",HIY+pinji[level]+NOR);
		me->set("mytitle/quest/guanfutitle",HIC+pinji[level]+NOR);		
		
		me->add("combat_exp", exp);
		me->add("potential", pot);
		if( me->query("potential") > me->query("max_pot") * 3 )
			me->set("potential", me->query("max_pot")); 
		me->add("shen", exp * 2);
		me->add("balance", exp * 50);
		me->start_busy(3);
        tell_object(me, "\n你得到了赏金"+MONEY_D->money_str(exp*50)+"，"+chinese_number(pot)+"点潜能和"+chinese_number(exp)+"点经验！\n");
		tell_object(me, "你的赏金可去钱庄提取。\n");
		me->set("job_name","官府捕快");
		log_file("job/guanfu", sprintf("%-18s 通缉任务，得 %4d Exp，%4d Pot，目前Exp：%d\n",
          		me->name()+"("+me->query("id")+")", exp, pot, me->query("combat_exp")),me);
		del_wanted(id);	
	}
	else tell_object(me, "Error! 请通知巫师。\n");
}

string *act = ({ "杀人抢劫", "偷摸拐骗", "拦路抢劫", "入室杀人", "杀人拒捕", "劫狱潜逃", "越狱潜逃", "谋财害命" });

private int do_wanted(object ob, mixed info)
{	
	string id, place;
	int exp;
	
        if (!ob->is_character() ) return 0;
        id = ob->query("id");
        if ( mapp(wanted[id]) ) return 0;
        	
        if( !mapp(info) ){
                exp = ob->query("combat_exp") / 2500;
        	if ( exp > 800 ) exp = 800;
        	exp = exp/2 + random(exp/2);
        	if (!stringp(place = base_name(environment(ob))) )
        		place = "中原神州";
        	else place = TASK_D->get_regions(base_name(environment(ob)))+environment(ob)->query("short");
        	info = ([
        		"name" 	: ob->name(1),
        		"reward": exp,
        		"exp"   : ob->query("combat_exp"),
        		"gender": ob->query("gender"),
        		"level"	: "/cmds/std/look"->gettof(ob, 2),
        		"age"	: ob->query("age"),
        		"act"	: act[random(sizeof(act))],
        		"action": random(2)?"就地格杀":"缉拿归案",
        		"place" : place,
        		"base"	: ob,
        		"wenshu": 2+random(5),
        	]);
        }
	ob->set("gf_wanted_info", info);
	
        if( wanted[id] = info ) return 1;
	else return 0;
}

int do_jie(string arg)
{
        object me, wenshu;
        mapping target;
        int i, exp;
	string str;
	
	me = this_player();
	if (me->is_busy() || me->is_fighting() ) 
		return notify_fail("你先忙完了再说吧。\n");
	
	me->start_busy(2);
	
        if (!arg)
        	return notify_fail("你揭开地上一片瓦片看了看。\n");

	if ( !query_wanted_size() ) 
		return notify_fail("目前通缉榜上还没出什么官府文书，看来治安还不错？！\n");
	
	if (me->query_condition("job_busy"))
                return notify_fail("你现在任务缠身，忙不过来呢！\n");
                
        if ( objectp(wenshu = present("tiebu wenshu", me)) )
                return notify_fail("你身上还揣着榜呢，可以通过(look wenshu)来查询！\n");
                
        if (!mapp(target = wanted[arg]) ) {
        	message_vision("$N揭开地上一块刻了「"+arg+"」的方砖看了看，惹得旁人都悄悄议论：“这人是在找"+(random(2)?"蚂蚁":"蛐蛐")+"吧？”\n", me);
        	return 1;
        }
        
// 没定义wenshu数量的，按5张算。
        if ( !intp(i = target["wenshu"]) )
        	return notify_fail("此犯的铁捕文书已经全部被揭走了！\n");
        	
        str = (string)target["name"];
        exp = (int)me->query("combat_exp"); 
        
        if( exp < 100000 ){
        	message_vision("$N挤上前去刚想伸手，忽然看到上面凶神恶煞的画像，吓得一下把手缩了回来。\n", me);
                return notify_fail("你想了想，觉得自己的这点功夫，还是算了吧。\n"); 
        }
        
        else if( exp > 1500000 )
        	message_vision(HIY"\n$N分开行人来到近前，目光淡淡的扫视了几眼告示，嘴角微微一翘，神态自如的把通缉"+str+"的文书揭了下来。\n"NOR, me);
        
        else if( exp > 900000 )
        	message_vision(HIY"\n$N推开围观的行人，走到近前，微微睁开眼睛，冷冷瞥了一眼告示，随手揭了通缉"+str+"的文书下来揣进了怀中。\n"NOR, me);
        
        else if( exp > 300000 )
        	message_vision(HIY"\n$N走上前去看了看，“唰”地一下把通缉"+str+"的文书揭了下来，转身走出人群。\n"NOR, me);
        
        else 	message_vision(HIY"\n$N壮了壮胆，费力拔开行人，来到近前深深吸了口气，竭力镇定一下紧张的心情，四下看了看，悄悄把文书揭了下来。\n"NOR, me);
        
        str = "\t"+str+"("+capitalize(arg)+")\n";
        str += "\t"+chinese_number(target["age"])+"岁"+target["gender"]+"，武功"+target["level"]+"\n";
        str += "\t此人"+target["act"]+"后，最后一次出现在"+target["place"]+"附近。\n";
        str += "\t"+target["action"]+"的赏金："+MONEY_D->money_str(target["reward"]*50)+"。\n\n";
        str += "\t\t\t知府衙门\n\n";
        
        wenshu = new(MISC_D("gf_wenshu"));
        if (!wenshu || !clonep(wenshu) )
        	return notify_fail("错误！请通知巫师：GF_job -> wenshu doest not exist! \n");
        i--;
        wenshu->set("long", WHT"这是一张铁捕文书，可以拘捕(jubu)犯人，上面有一个画像，底下有一行小字：\n\n"NOR+str);
        wenshu->set("target", target);
        wenshu->set("target/id", arg);
        wenshu->move(me);
        
        if( i <= 0 ) del_wanted(arg);
        return 1;
}

string *wheres=({
"/d/emei/xiaowu",		"/d/wudang/xiaolu1",		"/d/xiangyang/zhuquemen",
"/d/xiangyang/hanshui1",	"/d/jiaxing/nanhu",		"/d/xueshan/xuelu2",
"/d/xueshan/houzidong",		"/d/suzhou/lingyansi",		"/d/suzhou/liuyuan",
"/d/jiaxing/tieqiang",		"/d/hz/longjing",		"/d/hz/huanglong",
"/d/hz/yuhuang",		"/d/hz/tianxiang",		"/d/miaojiang/jiedao4",
"/d/foshan/duchang",		"/d/huanghe/shulin6",		"/d/hz/changlang1",
"/d/hz/yuquan",			"/d/hz/longjing",		"/d/xingxiu/shamo3",
"/d/wudang/xuanyue",		"/d/emei/guanyinqiao",		"/d/emei/basipan3",
"/d/tiezhang/shanmen",		"/d/tiezhang/hclu",		"/d/xueshan/huilang4",
"/d/emei/caopeng",		"/d/mingjiao/bishui",		"/d/mingjiao/shanting",
"/d/fuzhou/haigang",		"/d/fuzhou/laozhai",		"/d/xingxiu/shamo2",
"/d/jiaxing/nanhu",		"/d/village/caidi",		"/d/shaolin/songshu2",
"/d/xiangyang/tanxi",		"/d/huashan/husun",		"/d/huashan/yunu",
"/d/mr/yanziwu/xiaojing2",	"/d/mr/mtl/liulin",		"/d/suzhou/shihu",
"/d/suzhou/xuanmiaoguan",	"/d/suzhou/zijinan",		"/d/hengshan/cuiping2",
"/d/hengshan/guolaoling",	"/d/shaolin/talin1",		"/d/wudang/houshan/husunchou",
"/d/shaolin/shanlu8",		"/d/xueshan/shanlu7",		"/d/foshan/road10",
"/d/foshan/xiaolu2",		"/d/emei/jiulaodong",		"/d/hengshan/beiyuemiao",
"/d/gb/xinglin2",		"/d/city/shangang",		"/d/fuzhou/zhongxin",
"/d/huanghe/huanghe4",		"/d/lanzhou/shamo",		"/d/emei/gudelin3",
"/d/cangzhou/dongjie1",		"/d/tanggu/center",		"/d/putian/xl6",
"/d/dali/wuliang/songlin6",	"/d/gumu/xuantie/linhai8",	"/d/gumu/jqg/zhulin5",
"/d/tianshan/dadao6",		"/d/tianshan/shanjin5",		"/d/hmy/changlang",
"/d/hmy/taohua",		"/d/kunlun/shanlin2",		"/d/thd/guiyun/jiugong2",
});

private int random_goto(object ob)
{
	object room;
	int i;
	i = random(sizeof(wheres));
	if( !objectp(room= find_object(wheres[i])) ){
		if( !objectp(room= load_object(wheres[i])) ){
			destruct(ob);
			log_file("job/gfbug",sprintf("GF_wanted.c loading "+wheres[i]+" 失败。\n"));
			return 0;
		}
		if( ob->move(room) ) return 1;
		else {
			destruct(ob);
			log_file("job/gfbug", sprintf("GF_wanted.c NPC goto "+wheres[i]+" 失败。\n"));
		}
	}
	if( ob->move(room) ) return 1;
	else {
		destruct(ob);
		log_file("job/gfbug",sprintf("GF_wanted.c NPC goto "+wheres[i]+" 失败。\n"));
		return 0;
	}
}

private void creat_npc(object *obs)
{
	object player, ob, room;
	string room_name;
	
	ob = new(WANTED_NPC);
	ob->copy_random_player(obs);
	
	if( random(4) != 1 || !sizeof(obs) ){
		random_goto(ob);
	}
	
	else {
		player = obs[random(sizeof(obs))];
		if( environment(player)->is_character() )	
			room = environment(environment(player));
	
		if (wiz_level(player)
		|| player->is_ghost()
		|| !living(player)
		|| !objectp(room)
		|| strsrch(room_name = base_name(room),"/d/") != 0
		|| strsrch(room_name, "/d/wizard/") == 0
		|| strsrch(room_name, "/d/wuguan/") == 0
		|| strsrch(room_name, "/d/death/") == 0) 
        		random_goto(ob);
	
		else if( !ob->move(room) ){
			destruct(ob);
			log_file("job/gfbug", sprintf("GF_wanted.c -> creat_wanted() -> NPC goto 失败。\n"));
			return;
		}
	}
	if( ob ){
		if( do_wanted(ob, 0) ){
			modify_list(0);
			return;
		}
		
		else{
			destruct(ob);
			return notify_fail("Gf_wanted.c -> do_wanted() failed!\n");
		}
	}
	else return notify_fail("Gf_wanted.c -> failed to creat wanted ob !\n");
}


void create()
{
	object *obs;
	modify_list(1);

	remove_call_out("create");
	call_out("create", 800+random(400));

	obs = filter_array(users(), (:  environment($1) && !wizardp($1) && ($1->query("registered") > 1) && $1->query_temp("user_type") != "worker" :));
	if( !obs || sizeof(obs) < 1 ) return;

	creat_npc(obs);
	creat_npc(obs);
	creat_npc(obs);
	creat_npc(obs);
	creat_npc(obs);
	creat_npc(obs);
	creat_npc(obs);
	tell_room(WANTED_ROOM, "\n从衙门内走来几名衙役，在告示前忙活了一阵。\n\n");
	message("system",HIR"【扬州知府通告】近日有恶贼行凶作乱，请各位江湖豪杰速来官府领取铁捕文书，协助将彼等缉拿归案。\n"NOR, users());
}
