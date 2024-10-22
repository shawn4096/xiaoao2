// top.c yuj@sj 2000-1-16
// add pk beauty weapon armor 
// score 计算部分多多指正 Ciwei@SJ

inherit F_CLEAN_UP;
inherit F_SAVE;

#include <ansi.h>
#include <mudlib.h>
#include <database.h>

mapping *score_ranks;
mapping *beauty_ranks;
mapping *pk_ranks;
mapping *rich_ranks;
mapping *worker_ranks;
mapping *was_ranks;
mapping *gmd_ranks;


nosave int score_total = 99;
nosave int beauty_total = 99;
nosave int pk_total = 99;
nosave int rich_total = 20;
nosave int worker_total = 10;
nosave int was_total = 99;
nosave int gmd_total = 99;

nosave int count_add = 0;

nosave int now_num;
nosave int now_type;
nosave int now_status = 0;

int show_worker_rank(object me,string type,int j);

void create()
{
	seteuid(getuid());
	restore();
}

int remove()
{
	save();
	return 1;
}

string query_save_file()
{
	return "/log/rank";
}

int sort_rank(mapping rank1, mapping rank2)
{
	reset_eval_cost(); // added by snowman@SJ
	return rank2["score"]-rank1["score"];
}

int clean_all()
{
	score_ranks = ({ });
	beauty_ranks = ({ });
	pk_ranks = ({ });
	rich_ranks = ({ });
	worker_ranks = ({ });
	was_ranks = ({ });
	gmd_ranks = ({ });

	return remove();
}

void put_in_db()
{
	string subject,type,content;
	
	now_status = 1;
	
	switch(now_type){
		case 1:
			subject = CHINESE_MUD_NAME+" PLMM List";
			type    = "beauty";
			break;
		case 2:
			subject = CHINESE_MUD_NAME+" PKER List";
			type    = "pk";
			break;
		default:
			now_status = 0;
			return;
	}
	now_num=0;
	content = "<table width='97%' border='0' align='center' bgcolor='#000000'>
  <tr>
    <td height='317'><div align='center'><BR>
        <strong><font color='#FFFF00' face='Fixedsys'>" + subject + "("+CHINESE_D->chinese_date(time(),1)+")</font></strong><font face='Fixedsys'><br>
        </font></div>
      <table width='70%' border='0' align='center' cellpadding='4' cellspacing='3' bgcolor='#000000'>
        <tr align=center> 
          <td width='10%' height='30'><font color='#00FF00' face='Fixedsys'><strong>名次</strong></font></td>
          <td width='30%' height='30'><font color='#00FF00' face='Fixedsys'><strong>门派</strong></font></td>
          <td width='30%' height='30'><font color='#00FF00' face='Fixedsys'><strong>姓名</strong></font></td>
          <td width='30%' height='30'><font color='#00FF00' face='Fixedsys'><strong>综合评价</strong></font></td>
        </tr>";        
        content = replace_string(content,"'","\"");
	if (BBS_D->add_Bbs_Up_Map(WEB_DB_NAME, "REPLACE INTO mud_info (subject, utime, content, type, site) values ('"+subject+"', '"+time()+"','"+content+"', '"+type+"', '"+lower_case(INTERMUD_MUD_NAME)+"')",this_object(),"goon_upload"));
}

void goon_upload(mixed ret)
{
        int i = 0;
        string str="";
        string sql;
        mapping *now_map;
        string subject;
        int max = now_num+10;
        
        switch(now_type){
		case 1:
			subject = CHINESE_MUD_NAME+" PLMM List";			
			now_map = beauty_ranks;
			break;
		case 2:
			subject = CHINESE_MUD_NAME+" PKER List";			
			now_map = pk_ranks;
			break;
		case 3:
			subject = CHINESE_MUD_NAME+" WASTOP List";			
			now_map = was_ranks;
			break;
		case 4:
			subject = CHINESE_MUD_NAME+" GMDTOP List";			
			now_map = gmd_ranks;
			break;
		default:return;
	}
        if(max>sizeof(now_map)) max=sizeof(now_map);
        for(i=now_num;i<max;i++){
        	//名次 名字 门派 综合评价
        	str += sprintf("<tr align=center> 
          <td><font color='#008000' face='Fixedsys'>No.%d</font></td>
          <td><font color='#008000' face='Fixedsys'>%s</font></td>
          <td><font color='#008000' face='Fixedsys'>%s</font></td>
          <td><font color='#008000' face='Fixedsys'>%d</font></td>
          </tr>",
          i+1,now_map[i]["family"],now_map[i]["name"],now_map[i]["score"],
          );
        }
        str = replace_string(str,"'","\"");
        now_num += 10;
        if(str!="") 
        {
        sql = sprintf("UPDATE mud_info SET content = CONCAT(content,'%s') WHERE subject='%s' AND site = '%s'",
        str,subject,lower_case(INTERMUD_MUD_NAME));
        BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,sql,this_object(),"goon_upload");        
        }
        else {
		str += "</table><br></td></tr></table>";
                str = replace_string(str,"'","\"");
                sql = sprintf("UPDATE mud_info SET content = CONCAT(content,'%s') WHERE subject='%s' AND site = '%s'",
                str,subject,lower_case(INTERMUD_MUD_NAME));
                now_type += 1;
                BBS_D->add_Bbs_Up_Map(WEB_DB_NAME,sql,this_object(),"put_in_db");                
        }
}

void add_rank_beauty(object ob)
{
	int i, score, t = time();
	mapping rank;
	string party = ob->query("family/family_name");

	// 先删除原先记录	
	for (i = 0; i < sizeof(beauty_ranks); i++)
		if (wiz_level(beauty_ranks[i]["id"]) || beauty_ranks[i]["id"] == ob->query("id") || beauty_ranks[i]["score"] < 1) {
			beauty_ranks = beauty_ranks[0..i-1] + beauty_ranks[i+1..beauty_total];
			i--;
		}
	
	if (ob->query("age") < 16) return; //改成16岁
	if (ob->query("gender")!="女性") return;
	if (wiz_level(ob)) return;
	score = ob->query_per()*30
		-ob->query_skill("beauty",1)/3
		-ob->query("divorce")*5
		-ob->query("age")
		+20;
	if(ob->query("age")<22){
		score = score * ob->query("age");
		score = score / 22;//含苞待放 ^_^
	}
	if( score < 1 ) return;

	for (i = 0; i < sizeof(beauty_ranks); i++)
		if (!find_player(beauty_ranks[i]["id"]))
			while (beauty_ranks[i]["time"]+3600 < t) {
				beauty_ranks[i]["time"] += 3600;
				beauty_ranks[i]["score"] *= 95;
				beauty_ranks[i]["score"] /= 100;
			}
		else beauty_ranks[i]["time"] = t;

	if (!sizeof(beauty_ranks)) beauty_ranks = ({ });
	beauty_ranks = sort_array(beauty_ranks, (: sort_rank :));

	for (i = 0; i < sizeof(beauty_ranks); i++)
		if (score > beauty_ranks[i]["score"]) break;
	if (i > beauty_total) return;

	if (!stringp(party)) party = "普通百姓";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,
			"time":         t,
			"score":        score ]);
	if (!sizeof(beauty_ranks))
		beauty_ranks = ({ rank });
	else
		beauty_ranks = beauty_ranks[0..i-1] + ({ rank }) + beauty_ranks[i..beauty_total];
}

void add_rank_was(object ob)
{
	int i, score, t = time();
	int exp = ob->query("combat_exp");
	mapping rank;
	string party = ob->query("family/family_name");
	mapping *notes;
	mapping note;
	string file;
  
	// 先删除原先记录	
	for (i = 0; i < sizeof(was_ranks); i++)
		if (wiz_level(was_ranks[i]["id"]) || was_ranks[i]["id"] == ob->query("id") || was_ranks[i]["score"] < 1) {
			was_ranks = was_ranks[0..i-1] + was_ranks[i+1..was_total];
			i--;
		}
	
	if (wiz_level(ob)) return;
	if (exp <  10000000 ) return;//10M以前还能闯关？wink	
	
	
	score = ob->query("was_job/level")*1;
	
	if( score < 1 ) return;
	
	if (!sizeof(was_ranks)) was_ranks = ({ });	
		
	was_ranks = sort_array(was_ranks, (: sort_rank :));

	for (i = 0; i < sizeof(was_ranks); i++)
		if (score > was_ranks[i]["score"]) break;
	if (i > was_total) return;

	if (!stringp(party)) party = "普通百姓";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,
			"time":         t,
			"score":        score ]);
	if (!sizeof(was_ranks))
		was_ranks = ({ rank });
	else
		was_ranks = was_ranks[0..i-1] + ({ rank }) + was_ranks[i..was_total];
}

void add_rank_gmd(object ob)
{
	int i, score, t = time();
	int exp = ob->query("combat_exp");
	mapping rank;
	string party = ob->query("family/family_name");
	mapping *notes;
	mapping note;
	string file;
  
	// 先删除原先记录	
	for (i = 0; i < sizeof(gmd_ranks); i++)
		if (wiz_level(gmd_ranks[i]["id"]) || gmd_ranks[i]["id"] == ob->query("id") || gmd_ranks[i]["score"] < 1) {
			gmd_ranks = gmd_ranks[0..i-1] + gmd_ranks[i+1..gmd_total];
			i--;
		}
	
	if (wiz_level(ob)) return;
	if (exp <  10000000 ) return;//10M以前还能闯关？wink	
	
	
	score = ob->query("gmd_job/level")*1;
	
	if( score < 1 ) return;
	
	if (!sizeof(gmd_ranks)) gmd_ranks = ({ });	
		
	gmd_ranks = sort_array(gmd_ranks, (: sort_rank :));

	for (i = 0; i < sizeof(gmd_ranks); i++)
		if (score > gmd_ranks[i]["score"]) break;
	if (i > gmd_total) return;

	if (!stringp(party)) party = "普通百姓";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,
			"time":         t,
			"score":        score ]);
	if (!sizeof(gmd_ranks))
		gmd_ranks = ({ rank });
	else
		gmd_ranks = gmd_ranks[0..i-1] + ({ rank }) + gmd_ranks[i..gmd_total];
}


void add_rank_pk(object ob)
{
	int i, score, t = time();
	int exp = ob->query("combat_exp");
	mapping rank;
	string party = ob->query("family/family_name");

	// 先删除原先记录	
	for (i = 0; i < sizeof(pk_ranks); i++)
		if (wiz_level(pk_ranks[i]["id"]) || pk_ranks[i]["id"] == ob->query("id") || pk_ranks[i]["score"] < 1) {
			pk_ranks = pk_ranks[0..i-1] + pk_ranks[i+1..pk_total];
			i--;
		}

	if (wiz_level(ob)) return;
	if (exp <  100000 ) return;//100K以前还能叫杀手么？wink
	score = ob->query("PKS")*40
		+ob->query("FKS")*50
		+((ob->query("PKS")+ob->query("FKS"))*5000-ob->query("MKS"))/150;
	if( score < 1 ) return;
	
	for (i = 0; i < sizeof(pk_ranks); i++)
		if (!find_player(pk_ranks[i]["id"]))
			while (pk_ranks[i]["time"]+3600 < t) {
				pk_ranks[i]["time"] += 3600;
				pk_ranks[i]["score"] *= 97;
				pk_ranks[i]["score"] /= 100;
			}
		else pk_ranks[i]["time"] = t;

	if (!sizeof(pk_ranks)) pk_ranks = ({ });
	pk_ranks = sort_array(pk_ranks, (: sort_rank :));

	for (i = 0; i < sizeof(pk_ranks); i++)
		if (score > pk_ranks[i]["score"]) break;
	if (i > pk_total) return;

	if (!stringp(party)) party = "普通百姓";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,			
			"time":         t,
			"score":        score ]);
	if (!sizeof(pk_ranks))
		pk_ranks = ({ rank });
	else
		pk_ranks = pk_ranks[0..i-1] + ({ rank }) + pk_ranks[i..pk_total];
}

void add_rank_rich(object ob)
{
	int i, score, t = time();
	int exp = ob->query("combat_exp");
	int balance = ob->query("SJ_Credit",1);
	mapping rank;
	string party = ob->query("family/family_name");
	
	// 先删除原先记录	
	for (i = 0; i < sizeof(rich_ranks); i++)
		if (wiz_level(rich_ranks[i]["id"]) || rich_ranks[i]["id"] == ob->query("id") || rich_ranks[i]["score"] < 1) {
			rich_ranks = rich_ranks[0..i-1] + rich_ranks[i+1..rich_total];
			i--;
		}
		
	if (wiz_level(ob)) return;
	if (exp <  100 ) return;
	if ( balance < 1000) return;
	score = balance ;
	if( score < 1 ) return;
		
	for (i = 0; i < sizeof(rich_ranks); i++)
		if (!find_player(rich_ranks[i]["id"]))
			while (rich_ranks[i]["time"]+3600 < t) {
				rich_ranks[i]["time"] += 3600;
				rich_ranks[i]["score"] *= 97;
				rich_ranks[i]["score"] /= 100;
			}
		else rich_ranks[i]["time"] = t;

	if (!sizeof(rich_ranks)) rich_ranks = ({ });
	rich_ranks = sort_array(rich_ranks, (: sort_rank :));

	for (i = 0; i < sizeof(rich_ranks); i++)
		if (score > rich_ranks[i]["score"]) break;
	if (i > rich_total) return;

	if (!stringp(party)) party = "普通百姓";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,			
			"time":         t,
			"score":        score ]);
	if (!sizeof(rich_ranks))
		rich_ranks = ({ rank });
	else
		rich_ranks = rich_ranks[0..i-1] + ({ rank }) + rich_ranks[i..rich_total];
}


void add_rank_worker(object ob)
{
	int i, score, t = time();
	int exp = ob->query("combat_exp");	
	mapping rank;
	string party = ob->query("family/family_name");
	
	// 先删除原先记录	
	for (i = 0; i < sizeof(worker_ranks); i++)
		if (wiz_level(worker_ranks[i]["id"]) || worker_ranks[i]["id"] == ob->query("id") || worker_ranks[i]["score"] < 1) {
			worker_ranks = worker_ranks[0..i-1] + worker_ranks[i+1..worker_total];
			i--;
		}
		
	if (wiz_level(ob)) return;
	if (exp <  100000 ) return;
	
	score =  ob->query_skill("duanzao",1);
	if(ob->query_skill("duanzao",1) > 250 ) score+= (ob->query_skill("duanzao",1) - 250) * ob->query_skill("duanzao",1) / 250;
	score += ob->query_skill("zhizao",1);
	if(ob->query_skill("zhizao",1) > 250 ) score+= (ob->query_skill("zhizao",1) - 250) * ob->query_skill("zhizao",1) / 250;
	score += ob->query_skill("caiji",1);
	if(ob->query_skill("caiji",1) > 250 ) score+= (ob->query_skill("caiji",1) - 250) * ob->query_skill("caiji",1) / 250;
	score += ob->query_skill("caikuang",1);
	if(ob->query_skill("caikuang",1) > 250 ) score+= (ob->query_skill("caikuang",1) - 250) * ob->query_skill("caikuang",1) / 250;
	
	if( score < 1 ) return;
		
	for (i = 0; i < sizeof(worker_ranks); i++)
		if (!find_player(worker_ranks[i]["id"]))
			while (worker_ranks[i]["time"]+3600 < t) {
				worker_ranks[i]["time"] += 3600;
				worker_ranks[i]["score"] *= 97;
				worker_ranks[i]["score"] /= 100;
			}
		else worker_ranks[i]["time"] = t;

	if (!sizeof(worker_ranks)) worker_ranks = ({ });
	worker_ranks = sort_array(worker_ranks, (: sort_rank :));

	for (i = 0; i < sizeof(worker_ranks); i++)
		if (score > worker_ranks[i]["score"]) break;
	if (i > worker_total) return;
	
	if (!stringp(party)) party = "普通百姓";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,			
			"time":         t,
			"score":        score ]);
	if (!sizeof(worker_ranks))
		worker_ranks = ({ rank });
	else
		worker_ranks = worker_ranks[0..i-1] + ({ rank }) + worker_ranks[i..rich_total];
}

void add_rank(object ob)
{
	int i, score, t = time();
	int exp = ob->query("combat_exp");
	int age = ob->query("mud_age") / 3600;
	mapping rank;
	string party = ob->query("family/family_name");
		
	add_rank_beauty(ob);
	add_rank_was(ob);
	add_rank_gmd(ob);
	add_rank_pk(ob);
	add_rank_rich(ob);
	add_rank_worker(ob);	
	// 先删除原先记录
	
	for (i = 0; i < sizeof(score_ranks); i++)
		if (wiz_level(score_ranks[i]["id"]) || score_ranks[i]["id"] == ob->query("id") || score_ranks[i]["score"] < 1) {
			score_ranks = score_ranks[0..i-1] + score_ranks[i+1..score_total];
			i--;
		}

	if (wiz_level(ob)) return;
	if (age < 10 || exp < 1) return;
	score =  (exp + ob->query("relife/gifts/total")* 5000000 +  ob->query("relife/exp_ext")* 5000000 ) / 1000 * (
		ob->query_int(1)*9/10
		+ob->query_str(1)*11/10
		+ob->query_dex(1)
		) / 1000
		+ to_int(ob->query_con(1)
			* ob->query("max_neili") / 200.0 * ob->query("max_neili") / 20000)
		+ to_int(ob->query_con(1)
			* ob->query("max_jingli") / 100.0 * ob->query("max_jingli") / 20000);
	ob->set("score", score);
	if( score < 1 ) return;

	for (i = 0; i < sizeof(score_ranks); i++)
		if (!find_player(score_ranks[i]["id"]))
			while (score_ranks[i]["time"]+3600 < t) {
				score_ranks[i]["time"] += 3600;
				score_ranks[i]["score"] *= 97;
				score_ranks[i]["score"] /= 100;
			}
		else score_ranks[i]["time"] = t;

	if (!sizeof(score_ranks)) score_ranks = ({ });
	score_ranks = sort_array(score_ranks, (: sort_rank :));

	for (i = 0; i < sizeof(score_ranks); i++)
		if (score > score_ranks[i]["score"]) break;
	if (i > score_total) return;

	if (!stringp(party)) party = "普通百姓";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,
			"exp":          exp,
			"eoh":          exp / age,
			"time":         t,
			"score":        score ]);
	if (!sizeof(score_ranks))
		score_ranks = ({ rank });
	else
		score_ranks = score_ranks[0..i-1] + ({ rank }) + score_ranks[i..score_total];
	save();
	count_add += 1;
	if(count_add%100==0 && !now_status ){
		now_type = 1;
		//put_in_db();
	}
}

void remove_busy(object me)
{
	if (me) me->delete_temp("command_busy");
}

int main(object me, string arg)
{
	int i, j;
	string str = "\n              ┏ 书剑高手排行榜 ┓\n";
	int flag = wizardp(me), t = time()-3600-119;
	string type;
	mapping *ranks = score_ranks;
	int total = score_total;
	
	if (!wizardp(me) && me->query_temp("command_busy"))
		return notify_fail("你正忙着呢。\n");
	me->set_temp("command_busy",1);
	call_out("remove_busy", 3, me);
	if(!arg || ( stringp(arg) && sscanf(arg, "%d", j)==1 ) ) ;
	else {
		if(sscanf(arg,"%s %d",type,j)!=2) sscanf(arg,"%s",type);
		if(type=="armor" || type=="weapon")
			return show_worker_rank(me,type,j?j:10);
		if(type=="beauty"){
			str = "\n              ┏ 书剑美女排行榜 ┓\n";
			ranks = beauty_ranks;
		}
		if(type=="pk"){
			str = "\n              ┏ 书剑杀手排行榜 ┓\n";
			ranks = pk_ranks;
		}
		if(type=="rich"){
			str = "\n              ┏ 书剑富翁排行榜 ┓\n";
			ranks = rich_ranks;
		}
		if(type=="worker"){
			str = "\n              ┏ 书剑工匠排行榜 ┓\n";
			ranks = worker_ranks;
		}
		if(type=="was"){
			str = "\n              ┏ 万安寺闯关排行 ┓\n";
			ranks = was_ranks;
		}
		if(type=="gmd"){
			str = "\n              ┏ 光明顶闯关排行 ┓\n";
			ranks = gmd_ranks;
		}
		///etc....
	}
		
	if (me->query("combat_exp") > 100000 && !wiz_level(me))
		add_rank(me);
	
	str += "┏━━┯━━━┻━━━━━┯━━┻━┯━━━━┓\n";
	if(type=="was" || type=="gmd") {
		str += "┃名次│     名     字    │ 门  派 │闯关层数┃\n";
	}
	else		
	str += "┃名次│     名     字    │ 门  派 │综合评价┃\n";
	str += "┠──┴─────────┴────┴────┨\n";	
	if (j < 1)
		j = 10;
	if (j > total)
		j = total;
	if (j > sizeof(ranks))
		j = sizeof(ranks);
	for (i = 0; i < j; i++) {
		if(type=="was" || type=="gmd") {
			 str += sprintf("┃%s%|4d  %8s%-10s  %|8s  %|8s" NOR "┃%s\n",
			(ranks[i]["id"] == me->query("id"))?HIY BRED:"",
			i+1,
			ranks[i]["name"],
			"("+capitalize(ranks[i]["id"])+")",
			ranks[i]["family"],
			ranks[i]["score"]+"层",
			flag?sprintf("%'.'-30s", repeat_string("o", (ranks[i]["time"]-t)/120)):"");	  	
		}
		else
		{
			
		str += sprintf("┃%s%|4d  %8s%-10s  %|8s  %|8d" NOR "┃%s\n",
			(ranks[i]["id"] == me->query("id"))?HIY BRED:"",
			i+1,
			ranks[i]["name"],
			"("+capitalize(ranks[i]["id"])+")",
			ranks[i]["family"],
			ranks[i]["score"],
			flag?sprintf("%'.'-30s", repeat_string("o", (ranks[i]["time"]-t)/120)):"");
	
		}
	}
		str += "┗━━━━━━━━━━━━━━━━━━━━━━┛\n";
	me->start_more(str);
	return 1;
}

int show_worker_rank(object me,string type,int j)
{
	if(type!="weapon" && type!="armor") return 0;
	WORKER_D->show_rank(me,type,j);
	return 1;
}

int help(object me)
{
write(@HELP
指令格式 : 
top [数字] 		显示书剑高手排行榜
top weapon [数字]	显示书剑兵器排行榜
top armor  [数字]	显示书剑防具排行榜
top pk     [数字]	显示书剑杀手排行榜
top beauty [数字]	显示书剑美女排行榜
top was    [数字]	显示书剑万安寺闯关排行榜
top gmd    [数字]	显示书剑光明顶闯关排行榜

用途： 显示书剑高手、兵器、防具、杀手、美女排行榜，数字
表示显示数目。
HELP
     );
     return 1;
}

//add_rank_pk(ob);
//add_rank_rich(ob);
//add_rank_old(ob);


/*
void add_rank(object ob)
{
	int i, score, t = time();
	int exp = ob->query("combat_exp");
	int age = ob->query("mud_age") / 3600;
	mapping rank;
	string party = ob->query("family/family_name");

	// 先删除原先记录	
	for (i = 0; i < sizeof(ranks); i++)
		if (wiz_level(ranks[i]["id"]) || ranks[i]["id"] == ob->query("id") || ranks[i]["score"] < 1) {
			ranks = ranks[0..i-1] + ranks[i+1..total];
			i--;
		}

	if (wiz_level(ob)) return;
	if (age < 10 || exp < 1) return;
	score = exp / 200 * (
		ob->query_int(1)*9/10
		+ob->query_str(1)*11/10
		+ob->query_dex(1)
		) / 1000
//		+ exp / age
		+ to_int(ob->query_con(1)
			* ob->query("max_neili") / 40.0 * ob->query("max_neili") / 10000)
		+ to_int(ob->query_con(1)
			* ob->query("max_jingli") / 20.0 * ob->query("max_jingli") / 10000);
	ob->set("score", score);
	if( score < 1 ) return;

	for (i = 0; i < sizeof(ranks); i++)
		if (!find_player(ranks[i]["id"]))
			while (ranks[i]["time"]+3600 < t) {
				ranks[i]["time"] += 3600;
				ranks[i]["score"] *= 97;
				ranks[i]["score"] /= 100;
			}
		else ranks[i]["time"] = t;

	if (!sizeof(ranks)) ranks = ({ });
	ranks = sort_array(ranks, (: sort_rank :));

	for (i = 0; i < sizeof(ranks); i++)
		if (score > ranks[i]["score"]) break;
	if (i > total) return;

	if (!stringp(party)) party = "普通百姓";
	rank =  ([      "id":           ob->query("id"),
			"name":         ob->query("name"),
			"family":       party,
			"exp":          exp,
			"eoh":          exp / age,
			"time":         t,
			"score":        score ]);
	if (!sizeof(ranks))
		ranks = ({ rank });
	else
		ranks = ranks[0..i-1] + ({ rank }) + ranks[i..total];
	save();
}

*/
