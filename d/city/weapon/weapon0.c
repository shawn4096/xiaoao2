// 用于卖钱的武器，改变SJ金融状况，大部分原码来自Snowman dazao 系统 
#include <ansi.h>
string s_good(int i)
{
	switch(i){
		case 10..20:	return "无比";	
		case 9:		return "无比";	
		case 8:		return "极其";	
		case 7:		return "绝对";	
		case 6:		return "极为";	
		case 5:		return "相当";	
		case 4:		return "十分";	
		case 3:		return "非常";	
		case 2:		return "比较";	
		case 1:		return "还算";	
		case -1:	return "不怎么";	
		case -2:	return "很不";	
		case -3:	return "极不";	
		default:	return "一般";	
	}
}

string s_power(int i)
{
	if( i >= 300 )	return HIR"毁天灭地"NOR;
	if( i >= 280 )	return HIR"开元创世"NOR;	
	if( i >= 250 )	return HIR"天下无双"NOR;	
	if( i >= 220 )	return HIM"绝世罕见"NOR;	
	if( i >= 200 )	return HIY"举世无匹"NOR;
	if( i >= 180 )	return HIG"开天劈地"NOR;
	if( i >= 160 )	return HIB"倚天屠龙"NOR;
	if( i >= 140 )	return HIC"斩妖伏魔"NOR;
	if( i >= 120 )	return RED"无与伦比"NOR;
	if( i >= 100 )	return MAG"极其可怕"NOR;
	if( i >= 80 )	return YEL"很高"NOR;
	if( i >= 60 )	return GRN"水准以上"NOR;
	if( i >= 40 )	return BLU"不错"NOR;
	if( i >	20 )	return CYN"不小"NOR;
	if( i <= 0 )	return "极差";
	if( i <= -20 )	return "低劣";
	return "一般";
}

inherit EQUIP;
#include <mudlib.h>
#define PRICE 50 //定义武器出售的价格倍数

int weapon_setup(mapping mp);

void create()
{
	//set_name("长剑", ({ "chang jian","sword","jian" }));
	set_weight(5000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "柄");
		//set("value", 200);
		set("material", "steel");
		set("wield_msg", "$N拿出$n握在手中。\n");
		set("unwield_msg", "$N放下手中的$n。\n");
		set("wield_maxneili", 100);
		set("wield_neili", 10);
		set("wield_str", 20);		
	}
	set("flag", 4);
	set("verbs", ({ "slash", "hack", "slice", "thrust" }) );
	set("weapon_prop/damage", 1);
	set("skill_type", "sword");
	set("weapon_mp",
([ /* sizeof() == 23 */
  "long" : "",
  "skill_type" : "stick",
  "unit" : "根",
  "wield_neili" : 50,
  "verbs" : ({ /* sizeof() == 3 */
      "bash",
      "crush",
      "slam"
    }),
  "flag" : 16,
  "material" : "steel",
  "wield_msg" : "$N将$n握在手中。
",
  "weight" : 5154,
  "wield_str" : 17,
  "value" : 19800,
  "weapon_prop/damage" : 11,
  "id" : ({ /* sizeof() == 4 */
      "normal stick",
      "normal",
      "bang",
      "stick"
    }),
  "b_id" : "bang",
  "sharpness" : 0,
  "no_sell" : 1,
  "name" : "钢棒[0;0m",
  "basic_name" : "钢",
  "rigidity" : 1,
  "unwield_msg" : "$N将手中的$n放下。
",
  "wield_maxneili" : 500,
  "name_st" : ({ /* sizeof() == 1 */
      "加强锋利度"
    }),
  "imbued" : 1,
])
);
	set_name(query("weapon_mp")["name"], query("weapon_mp")["id"]);
	/*if (INTERMUD_MUD_NAME != "SJ")
	set("value",(query("weapon_mp")["value"]* PRICE ) > 15000000 ? 15000000 : query("weapon_mp")["value"] * PRICE );
	else
	set("value",(query("weapon_mp")["value"]* 2 ) > 15000000 ? 15000000 : query("weapon_mp")["value"] * 2 );
	*/
	//为什么要把溢出的注释？
	set("value",(query("weapon_mp")["value"]* PRICE ) > 15000000 ? 15000000 : query("weapon_mp")["value"] * PRICE );

	//set("value",query("weapon_mp")["value"]* PRICE );
	//设定value的最大值，再多要溢出了
	weapon_setup(query("weapon_mp"));
	setup();
}

int weapon_setup(mapping mp)
{
	string *vb;
	int i;
	mapping w_mp;
	string str = "";
	int p;
	int w;
	string st;
	
	
	if( !clonep(this_object()) )
		return 0;
	if( !mapp(mp) ) return 0;
	
	vb = keys(mp);
	
	for( i = 0; i < sizeof(vb); i++ )
		set(vb[i], mp[vb[i]]);
	
	set_name(mp["name"], mp["id"]);
	set_weight(mp["weight"]);
	set("actions", (: call_other, WEAPON_D, "query_action" :) );
	
	w_mp = query("weapon_mp");	
	
	
	if( stringp(w_mp["long2"]) )
		str = w_mp["long2"];
	str += "这是一"+w_mp["unit"]+"由" + s_good(w_mp["rigidity"]) + "坚硬的";

	switch(w_mp["material"]){
		case "xuantie":	str += BLU"玄铁"NOR; break;
		case "supersteel": str += "万年神铁"; break;
		case "greatsteel": str += "流花钢"; break;
		case "softsteel": str += "软铁"; break;
		case "bamboo": str += "斑竹"; break;
		case "wood": str += "檀木"; break;
		default: str +=	"精钢";	break;
	}
	w = w_mp["weight"];
	str +=	"制成，重"+sprintf("%s", chinese_number(w/500)+"斤"+chinese_number((w%500)/50)+"两"+chinese_number((w%50)/5)+"钱")+"的"+w_mp["name"]+"。\n";

	//mm = w_mp;
	if( intp( w_mp["weapon_prop/damage"] ) )
		p = w_mp["weapon_prop/damage"];
	else if( intp(w_mp["weapon_prop"]["damage"]) )
		p = w_mp["weapon_prop"]["damage"];
	else p = 0;
	
	str += "看起来"	+ ( w_mp["flag"]==4?s_good(w_mp["sharpness"])+"锋利，":"" ) + "具有"+ s_power(p) + "的威力！\n";
	str += "上面刻了三个数字：【"
		+ chinese_number(w_mp["wield_str"]) + "，"
		+ chinese_number(w_mp["wield_maxneili"]) + "，"
		+ chinese_number(w_mp["wield_neili"]) +	"】\n";

	if( w_mp["name_st"] ){
		if( stringp(w_mp["name_st"]) )
			str += "以及一排古篆字【 "HIG +	w_mp["name_st"]	+ NOR" 】\n\n";
		else if( sizeof(w_mp["name_st"]) > 0	){
			st = implode(w_mp["name_st"][0..<1], "、");
			str += "以及一排古篆字【 "HIG +	st + NOR" 】\n\n";
		}
	}
	set("long",str);
	delete("imbued");
	//价格可以调整……
	
	return 1;
}

int move(mixed dest, int silently)
{
			
	return ::move(dest, silently);
}

int weapon_fix()
{	
	delete("weapon_mp/broken");
	delete("broken");	
}
