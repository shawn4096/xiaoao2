// Modified by mxzhao 2004/02/18

#include <ansi.h>
inherit F_CLEAN_UP;
#include <mudlib.h>

string query(string name)
{
	if (name == "channel_id") return "调整精灵";
	return 0;
}

void skill_adjust(object ob)
 {
 	mapping skl, maps;
 	string *sname;
 	int i,lmt, death; 	
       int zs_attack, zs_damage, zs_armor,total,zs_defense;
	
	int st=ob->query("str"), intt=ob->query("int"), co=ob->query("con"), de=ob->query("dex");
	int ka=ob->query("kar"), pe=ob->query("per"), pu=ob->query("pur");
	int exp=ob->query("combat_exp");

	if (ob != this_player()) return;
	// bbb 这个变态写的 web 注册产生的一个垃圾
	ob->delete("max_naili");
	lmt = st+intt+co+de;
/*            if (!wiz_level(ob) && (lmt>84 || st>31 || intt>31 || co>31 || de>31 || ka>30 || pe>30 || pu>30))
		CHANNEL_D->do_channel(this_object(), "wiz",
			sprintf("%s(%s)天赋异禀：膂=%d 悟=%d 根=%d 身=%d 福=%d 容=%d 纯=%d 头四项和=%d",
                                ob->name(1), capitalize(ob->query("id")), st, intt, co, de, ka, pe, pu, lmt));
*/
	lmt = (int)ob->query("combat_exp");
	if (lmt < 0) lmt = 0;
	if (ob->query("shen") > lmt) ob->set("shen", lmt);
	if (ob->query("shen") < -lmt) ob->set("shen", -lmt);
	if (ob->query("reputation") > lmt) ob->set("reputation", lmt);
	for (i = to_int(pow(10.0 * lmt, 0.3333333));to_int(i*i/10.0*i)<=lmt;i++);
	lmt = i;
	ob->set("max_pot", 100 + lmt);
	if (ob->query("potential") > ob->query("max_pot"))
		ob->set("potential", ob->query("max_pot"));

	// skills & exp 检查	YUJ@SJ 2002-01-18
	skl = ob->query_skills();
	if (sizeof(skl)) {
		sname = keys(skl);
		foreach (string item in sname) {
			if (!intp(skl[item]) || skl[item] < 0) ob->delete_skill(item);
			else if (( SKILL_D(item)->type() == "martial" || SKILL_D(item)->type2() == "worker" ) && skl[item]> lmt) {
				tell_object(ob, sprintf("由于经验限制，你的「%s」从%s级降到了%s级。\n",
					to_chinese(item), chinese_number(skl[item]), chinese_number(lmt)));
				skl[item] = lmt;
				ob->improve_skill(item, (lmt+1)*(lmt+1), 1);
			}
		}
		switch (ob->query("family/family_name")) {
			case "昆仑派":
				if (skl["art"] > 100 ) {
					ob->add("max_jing", (skl["art"]/2-40)*(skl["xuantian-wuji"]/15));
					ob->add("max_qi", (skl["art"]/2-30)*(skl["xuantian-wuji"]/12));
					break;
				}
				if (skl["art"] > 180 && skl["xuantian-wuji"] >= 350) {
					ob->add("max_jing", (skl["art"]/2-40)*(skl["xuantian-wuji"]/15));
					ob->add("max_qi", (skl["art"]/2-30)*(skl["xuantian-wuji"]/15));
				}
				if (skl["art"] > 200 && skl["xuantian-wuji"] >= 450) {
					ob->add("max_jing", (skl["art"]/2-20)*(skl["xuantian-wuji"]/15));
					ob->add("max_qi", (skl["art"]/2-20)*(skl["xuantian-wuji"]/10));
				}
				break;
			case "少林派":
                if (skl["buddhism"] > 80) 
			   {
					ob->add("max_jing",(skl["buddhism"]/2-10)*(skl["yijin-jing"]/10));
					ob->add("max_qi",(skl["buddhism"]/2-10)*(skl["yijin-jing"]/10));
			    }
				if (skl["buddhism"] > 160 && skl["yijin-jing"] > 350)
				{
					ob->add("max_qi",(skl["buddhism"]/2)*(skl["yijin-jing"]/10));
					//ob->add("max_jing",(skl["buddhism"]/2-5)*(skl["yijin-jing"]/5));
				}		
				if (skl["buddhism"] > 200 && skl["yijin-jing"] > 450) {
					ob->add("max_jing",(skl["buddhism"]/2-30)*(skl["yijing-jing"]/10));
					ob->add("max_qi",(skl["buddhism"]/2-10)*(skl["yijing-jing"]/10));
			    }
				break;
			case "天龙寺":
				if (skl["buddhism"] > 80) {
					ob->add("max_jing",(skl["buddhism"]/2-30)*(skl["force"]/10));
					ob->add("max_qi",(skl["buddhism"]/2-10)*(skl["qiantian-yiyang"]/10));
			    }
				if (skl["buddhism"] >= 150&& skl["force"] > 350)
					ob->add("max_qi",(skl["buddhism"]/2-20)*(skl["kurong-changong"]/10));
				
				if (skl["buddhism"] > 200 && skl["force"] > 450) {
					ob->add("max_jing",(skl["buddhism"]/2-30)*(skl["force"]/10));
					ob->add("max_qi",(skl["buddhism"]/2-10)*(skl["force"]/10));
			    }
				break;
			case "铁掌帮":
				if (skl["tiezhang-xinfa"] > 80 ){
					ob->add("max_qi", (skl["tiezhang-xinfa"]/2-30)*(skl["guiyuan-tunafa"]/20));
					ob->add("max_jing", (skl["tiezhang-xinfa"]/2-40)*(skl["guiyuan-tunafa"]/20));
				}
				if (skl["tiezhang-xinfa"] > 150 &&skl["guiyuan-tunafa"] > 350){
					ob->add("max_qi", (skl["tiezhang-xinfa"]/2-30)*(skl["guiyuan-tunafa"]/20));
					ob->add("max_jing", (skl["tiezhang-xinfa"]/2-40)*(skl["guiyuan-tunafa"]/20));
				}
				if (skl["tiezhang-xinfa"] > 200 &&skl["guiyuan-tunafa"] > 450){
					ob->add("max_qi", (skl["tiezhang-xinfa"]/2-30)*(skl["guiyuan-tunafa"]/20));
					ob->add("max_jing", (skl["tiezhang-xinfa"]/2-40)*(skl["guiyuan-tunafa"]/20));
				}
			case "峨嵋派":
				if (skl["dacheng-fofa"] > 61)
					ob->add("max_jing",(skl["dacheng-fofa"]/2-30)*(skl["linji-zhuang"]/10));
				if (skl["dacheng-fofa"] > 101 && skl["linji-zhuang"] > 350)
					ob->add("max_qi",(skl["dacheng-fofa"]/2-10)*(skl["linji-zhuang"]/20));
				if (skl["dacheng-fofa"] > 200 &&skl["linji-zhuang"] > 450){
					ob->add("max_qi", (skl["dacheng-fofa"]/2-30)*(skl["linji-zhuang"]/20));
					ob->add("max_jing", (skl["dacheng-fofa"]/2-40)*(skl["linji-zhuang"]/20));
				}
				break;
			case "桃花岛":
				if (skl["qimen-bagua"] > 61){
					ob->add("max_qi", (skl["qimen-bagua"]/2-30)*(skl["bihai-chaosheng"]/15));
					ob->add("max_jing", (skl["qimen-bagua"]/2-30)*(skl["bihai-chaosheng"]/15));
				}
				if (skl["qimen-bagua"] >=100 && skl["bihai-chaosheng"] >=350){
					ob->add("max_qi", (skl["qimen-bagua"]/2-10)*(skl["bihai-chaosheng"]/15));
					ob->add("max_jing", (skl["qimen-bagua"]/2-30)*(skl["bihai-chaosheng"]/15));
				}
				if (skl["qimen-bagua"] >200 && skl["bihai-chaosheng"] >=450){
					ob->add("max_qi", (skl["qimen-bagua"]/2-10)*(skl["bihai-chaosheng"]/15));
					ob->add("max_jing", (skl["qimen-bagua"]/2-30)*(skl["bihai-chaosheng"]/15));
				}
				break;
			case "日月神教": //天魔诀和门派内功相配合
				if (skl["tianmo-jue"] > 61&& skl["tianmo-gong"] > 61){
					ob->add("max_qi", (skl["tianmo-jue"]/2-30)*(skl["tianmo-gong"]/15));
					ob->add("max_jing", (skl["tianmo-jue"]/2-30)*(skl["tianmo-gong"]/15));
				}
				if (skl["tianmo-jue"] > 100 && skl["xixing-dafa"] > 350){
					ob->add("max_qi", (skl["tianmo-jue"]/2-20)*(skl["xixing-dafa"]/10));
					ob->add("max_jing", (skl["tianmo-jue"]/2-20)*(skl["xixing-dafa"]/10));
				}
				if (skl["tianmo-jue"] > 200 && skl["xixing-dafa"] > 450){
					ob->add("max_qi", (skl["tianmo-jue"]/2-20)*(skl["xixing-dafa"]/10));
					ob->add("max_jing", (skl["tianmo-jue"]/2-20)*(skl["xixing-dafa"]/10));
				}
				break;
			case "武当派":
				if (skl["taoism"]<60) break;
			
			    if (skl["taoism"] > 200 && skl["yinyun-ziqi"] > 450)
			        ob->add("max_qi",(skl["taoism"]/2-10)*(skl["yinyun-ziqi"]/5)); //武当气加长
			    if (skl["taoism"] > 100 && skl["yinyun-ziqi"] > 350)
					ob->add("max_qi",(skl["taoism"]/2-10)*(skl["yinyun-ziqi"]/10));
				if (skl["taoism"] > 60 && skl["yinyun-ziqi"] > 150)
					ob->add("max_qi",(skl["taoism"]/4)*(skl["yinyun-ziqi"]/10));
				
				if (skl["taoism"] > 121)
					ob->add("max_jing",(skl["taoism"]/2-50)*(skl["yinyun-ziqi"]/20));
				break;
			case "全真教":
				
			    if (skl["taoism"] > 61)
					ob->add("max_qi",(skl["taoism"]/2-20)*(skl["xiantian-gong"]/10)); //增加全真的气
				
				if (skl["taoism"] >= 120 && skl["xiantian-gong"] >= 350) {
					ob->add("max_jing",(skl["taoism"]/2-30)*(skl["xiantian-gong"]/20));
					ob->add("max_qi",(skl["taoism"]/2-10)*(skl["xiantian-gong"]/10));
				}
				if (skl["taoism"] > 200 && skl["xiantian-gong"] >= 450) {
					ob->add("max_jing",(skl["taoism"]/2-20)*(skl["xiantian-gong"]/20));
					ob->add("max_qi",(skl["taoism"]/2-10)*(skl["xiantian-gong"]/10));
				}
				break;
				
            case "逍遥派":
				if (skl["art"] > 61)
					ob->add("max_qi",(skl["art"]/2-30)*(skl["beiming-shengong"]/10));
				if (skl["art"] >= 150 && skl["beiming-shengong"] >= 350)
                {
					ob->add("max_jing",(skl["art"]/2-30)*(skl["bahuang-gong"]/25));
					if (ob->query("gender")=="男性")
					    ob->add("max_qi",(skl["yangyanshu"]/2)*(skl["bahuang-gong"]/10));
					else ob->add("max_qi",(skl["yangyanshu"]/2)*(skl["bahuang-gong"]/20));			    
                }
				if (skl["art"] > 200 && skl["beiming-shengong"] >= 450)
                {
					ob->add("max_jing",(skl["art"]/2-50)*(skl["bahuang-gong"]/25));
					if (ob->query("gender")=="男性")
					    ob->add("max_qi",(skl["yangyanshu"]/2)*(skl["bahuang-gong"]/10));
					else ob->add("max_qi",(skl["yangyanshu"]/2)*(skl["bahuang-gong"]/20));			    
                }
				break;
            case "灵鹫宫":
				if (skl["yangyanshu"] > 61)
					ob->add("max_qi",(skl["yangyanshu"]/2-30)*(skl["bahuang-gong"]/10));
				if (skl["yangyanshu"] >150 && skl["bahuang-gong"] >= 350)
                {
					ob->add("max_jing",(skl["yangyanshu"]/2-50)*(skl["bahuang-gong"]/25));
					if (ob->query("gender")=="女性")
					    ob->add("max_qi",(skl["yangyanshu"]/2)*(skl["bahuang-gong"]/10));
					else ob->add("max_qi",(skl["yangyanshu"]/2)*(skl["bahuang-gong"]/20));
			    
}
				if (skl["yangyanshu"] >200 && skl["bahuang-gong"] >= 450)
                {
					ob->add("max_jing",(skl["yangyanshu"]/2-50)*(skl["bahuang-gong"]/25));
					if (ob->query("gender")=="女性")
					    ob->add("max_qi",(skl["yangyanshu"]/2)*(skl["bahuang-gong"]/10));
					else ob->add("max_qi",(skl["yangyanshu"]/2)*(skl["bahuang-gong"]/20));
			    
				}
				break;
			case "白驼山庄":
				if (skl["poison"] > 61)
				{
					ob->add("max_qi",(skl["poison"]/2-10)*(skl["hamagong"]/10));
					ob->add("max_jing",(skl["poison"]/2-10)*(skl["hamagong"]/30));
				}
				if (skl["poison"] >= 150&& skl["hamagong"] >= 350){
					ob->add("max_jing",(skl["poison"]/2-10)*(skl["hamagong"]/10));
					ob->add("max_qi",(skl["poison"]/2-10)*(skl["hamagong"]/10));
				}
				if (skl["poison"] > 200 && skl["hamagong"] >= 450){
					ob->add("max_jing",(skl["poison"]/2-10)*(skl["hamagong"]/10));
					ob->add("max_qi",(skl["poison"]/2-10)*(skl["hamagong"]/10));
				}

				break;
			case "星宿派":
				if (skl["poison"] > 61)
					ob->add("max_qi",(skl["poison"]/2-25)*(skl["huagong-dafa"]/10));
				
				if (skl["poison"] >= 150&& skl["huagong-dafa"] >= 350){
					ob->add("max_jing",(skl["poison"]/2-10)*(skl["huagong-dafa"]/20));
					ob->add("max_qi",(skl["poison"]/2-10)*(skl["huagong-dafa"]/10));
				}
				if (skl["poison"] > 150&& skl["huagong-dafa"] >= 450){
					ob->add("max_jing",(skl["poison"]/2-20)*(skl["huagong-dafa"]/20));
					ob->add("max_qi",(skl["poison"]/2-10)*(skl["huagong-dafa"]/10));
				}
				break;
			case "姑苏慕容":
				if (skl["murong-xinfa"] > 61)
					ob->add("max_qi",(skl["murong-xinfa"]/2-25)*(skl["shenyuan-gong"]/10));
				if (skl["murong-xinfa"] >= 150&& skl["shenyuan-gong"] >= 350){
					ob->add("max_jing",(skl["murong-xinfa"]/2-10)*(skl["shenyuan-gong"]/20));
					ob->add("max_qi",(skl["murong-xinfa"]/2-10)*(skl["shenyuan-gong"]/10));					
				}
				if (skl["poison"] > 200&& skl["huagong-dafa"] >= 450){
					ob->add("max_jing",(skl["murong-xinfa"]/2-20)*(skl["shenyuan-gong"]/20));
					ob->add("max_qi",(skl["murong-xinfa"]/2-10)*(skl["shenyuan-gong"]/10));
					ob->add("max_qi",(skl["murong-xinfa"]/2-10)*(skl["douzhuan-xingyi"]/10));
				}
				break;

			case "明教":
				if (skl["shenghuo-xinfa"] > 61)
					ob->add("max_qi",(skl["shenghuo-xinfa"]/2-25)*(skl["shenghuo-shengong"]/10));
				if (skl["shenghuo-xinfa"] >= 150&& skl["shenghuo-shengong"] >= 350){
					ob->add("max_jing",(skl["shenghuo-xinfa"]/2-10)*(skl["shenghuo-shengong"]/20));
					ob->add("max_qi",(skl["shenghuo-xinfa"]/2-10)*(skl["shenghuo-shengong"]/10));					
				}
				if (skl["shenghuo-xinfa"] > 200&& skl["shenghuo-shenggong"] >= 450){
					ob->add("max_jing",(skl["shenghuo-xinfa"]/2-20)*(skl["qiankun-danuoyi"]/20));					
					ob->add("max_qi",(skl["shenghuo-xinfa"]/2-10)*(skl["qiankun-danuoyi"]/10));
				}
				break;
			case "丐帮":
				/*death = ob->query("death_times");
				if ( death > 300 ) death = 300;
				if ( death > 1){*/
				if (skl["begging"] > 50) {
					ob->add("max_qi",(skl["begging"]/2)*(skl["huntian-qigong"]/20));
					//ob->add("max_qi", death * ob->query("con"));
					//ob->add("max_jing", death * ob->query("con"));
					//ob->add("max_qi", death * ob->query("con"));					
					ob->add("max_jing",(skl["begging"]/2)*(skl["huntian-qigong"]/20	));
				}
				if (skl["begging"] > 150 && skl["huntian-qigong"]>=350 )
				{
					ob->add("max_qi",(skl["begging"])*(skl["huntian-qigong"]/20));
				}
				if (skl["begging"] >200 && skl["huntian-qigong"]>=450)
				{
					ob->add("max_qi",(skl["begging"]/2-20)*(skl["huntian-qigong"]/20));
					//ob->add("max_jing",(skl["begging"]/2-40)*(skl["huntian-qigong"]/20));
				}
				break;
			case "大轮寺":
				if (skl["mizong-fofa"] > 61)
					ob->add("max_jing",(skl["mizong-fofa"]/2-30)*(skl["longxiang-boruo"]/10));
				if (skl["mizong-fofa"] > 150 && skl["longxiang-boruo"]>=350 )
				{
					ob->add("max_qi",(skl["mizong-fofa"])*(skl["longxiang-boruo"]/20));
				}
				if (skl["mizong-fofa"] >200 && skl["longxiang-boruo"]>=450)
				{
					ob->add("max_qi",(skl["mizong-fofa"]/2-20)*(skl["longxiang-boruo"]/20));
					ob->add("max_jing",(skl["mozong-fofa"]/2-40)*(skl["longxiang-boruo"]/20));
				}
				break;
			case "血刀门":
				if (skl["huanxi-chan"] > 81)
					ob->add("max_jing",(skl["huanxi-chan"]/2-40)*(skl["xuedao-jing"]/20));
				if (skl["jingang-liantishu"] > 100)
					ob->add("max_qi",(skl["huanxi-chan"]/2-30)*(skl["xuedao-jing"]/15));

				if (skl["huanxi-chan"] > 150 && skl["xuedao-jing"]>=350 && skl["jingang-liantishu"]>=350 )
				{
					ob->add("max_qi",(skl["huanxi-chan"])*(skl["xuedao-jing"]/20));
					ob->add("max_qi",(skl["huanxi-chan"])*(skl["jingang-liantishu"]/40));

				}
				if (skl["huanxi-chan"] >200 && skl["xuedao-jing"]>=450 && skl["jingang-liantishu"]>=450)
				{
					ob->add("max_qi",(skl["huanxi-chan"]/2-10)*(skl["xuedao-jing"]/10));
					ob->add("max_jing",(skl["huanxi-chan"]/2-40)*(skl["xuedao-jing"]/20));
				}
				break;
			case "古墓派":
				if (skl["suxin-jue"] > 61) 
				{
					ob->add("max_qi",(skl["suxin-jue"]/2-30)*10);
				}
				if (skl["suxin-jue"] > 150 && skl["yunu-xinjing"]>350)
				{
					
					ob->add("max_jing",(skl["suxin-jue"]/2-30)*(skl["yunu-xinjing"]/20));
					ob->add("max_qi",(skl["suxin-jue"]/2-20)*(skl["yunu-xinjing"]/20));
				}
				if (skl["yunu-xinjing"] >=450 && skl["suxin-jue"]>200) 
				{
					ob->add("max_jing",(skl["suxin-jue"]/2-40)*15);
					ob->add("max_qi",(skl["suxin-jue"]/2-20)*(skl["yunu-xinjing"]/20));
				}
				break; 
			case "神龙教":
               if (skl["shenlong-yaoli"] > 81 && skl["dulong-dafa"] > 81){
		   			ob->add("max_qi", (skl["shenlong-yaoli"]/2-30)*(skl["dulong-dafa"]/16));
					ob->add("max_jing", (skl["shenlong-yaoli"]/2-35)*(skl["dulong-dafa"]/25));
	   			}
			   if (skl["shenlong-yaoli"] >=150&&skl["dulong-dafa"] > 350){
		   			ob->add("max_qi", (skl["shenlong-yaoli"]/2-20)*(skl["dulong-dafa"]/15));
					ob->add("max_jing", (skl["shenlong-yaoli"]/2-35)*(skl["dulong-dafa"]/25));
	   			}
				if (skl["shenlong-yaoli"] >200&&skl["dulong-dafa"] > 450){
		   			ob->add("max_qi", (skl["shenlong-yaoli"]/2-20)*(skl["dulong-dafa"]/15));
					ob->add("max_jing", (skl["shenlong-yaoli"]/2-35)*(skl["dulong-dafa"]/25));
	   			}
				break;
			case "嵩山派":
				if (skl["songyang-jue"] > 60)
					ob->add("max_qi", skl["songyang-jue"]*4);
				if (skl["hanbing-zhenqi"] > 350 && skl["songyang-jue"] >= 100 )
				{
					ob->add("max_qi", (skl["songyan-jue"]/2-35)*(skl["hanbing-zhenqi"]/15));
					ob->add("max_jing",(skl["hanbing-zhenqi"]/2-40)*10);
				}
				if (skl["hanbing-zhenqi"] > 450 && skl["songyang-jue"] > 200 ) 
				{
					ob->add("max_qi", (skl["songyan-jue"]-20)*(skl["hanbing-zhenqi"]/10));
					//ob->add("max_jing",(skl["hanbing-zhenqi"]/2-100)*10);
				}
				break;
			case "华山派": //华山派正气诀和紫霞功配合加气和精
				if (skl["zhengqi-jue"] > 61 ){
                    ob->add("max_qi", (skl["zhengqi-jue"]/2-30)*(skl["force"]/20));
                   // ob->add("max_jing", (skl["ziyin-yin"]/2-10)*(skl["force"]/20));
				}
				if (skl["zhengqi-jue"] >=100&&skl["ziyin-yin"] >=100){
                    ob->add("max_qi", (skl["zhengqi-jue"]/2-10)*(skl["force"]/10));
                    ob->add("max_jing", (skl["ziyin-yin"]/2-20)*(skl["force"]/20));
				}
				if (skl["zhengqi-jue"] >200 &&skl["ziyin-yin"] >=200&& skl["zixia-gong"] >450){
                    ob->add("max_qi", (skl["zhengqi-jue"]/2-10)*(skl["zixia-gong"]/5));
                    ob->add("max_jing", (skl["ziyin-yin"]/5-20)*(skl["zixia-gong"]/20));
				}
				break; 
			//普通百姓
			default:
			/*	if( skl["hamagong"] ){
					ob->add("max_qi", skl["hamagong"] * 10);
					ob->add("max_jing", skl["hamagong"] * 10);
				}*/
				//百姓八段锦增加气和精血
				if( skl["baduan-jin"] ){
					ob->add("max_qi", skl["baduan-jin"] * 6);
					ob->add("max_jing", skl["baduan-jin"] * 6);
				}
			break;
		}
	}
// 加临时效果
       
	   
	   //100m以后补助精翻倍 by renlai
	  if (ob->query("combat_exp")>100000000)
	  {
		 ob->set_temp("jingbuff",1);
		 ob->add("max_jing",ob->query("max_jing")*2);
	  }
	   

        if( ob->query("relife/gifts/total") >0 && !ob->query_temp("gift_add_buff") )
		{
			total = ob->query("relife/gifts/total",1);
			//zs_attack= total *2+random(12);
			//zs_damage= total *2 +random(12);
			//zs_armor = total *2+random(12);
			
			zs_attack= total*3/2+random(10);
			zs_damage= total*2/3+random(10);
			//重新调整，参悟后的防御
			zs_armor = total*2+random(20);
			zs_defense = total*2+random(20); //新增defense ,强调参悟后防御
			
			ob->add_temp("apply/attack",zs_attack);
			ob->add_temp("apply/damage",zs_damage);
			ob->add_temp("apply/armor",zs_armor);
			ob->add_temp("apply/defense",zs_defense);
			ob->set_temp("gift_add_buff",1);
			ob->add("max_qi", total * ob->query("con")/2);
				  

			tell_object(ob,sprintf(BLINK+HBRED"你在娘缳玉洞领悟到的天赋使你额外获得了「%s」点命中率，「%s」点攻击伤害，「%s」点防御力,「%s」点躲避！"NOR"\n\n",
			chinese_number(zs_attack), chinese_number(zs_damage),chinese_number(zs_armor),chinese_number(zs_defense)));
      
        }

	// 加气
	//ob->add("max_qi", ob->query("max_neili") * ob->query("con") / 80);
	ob->add("max_qi", ob->query("max_neili") * ob->query("con") / 70);

	// enable 检查	YUJ@SJ 2002-01-18
	if (!mapp(skl)) skl = ([]);
	maps = ob->query_skill_map();
	if (sizeof(maps)) {
		sname = keys(maps);
		foreach (string item in sname) {
			if (!stringp(maps[item])) continue;
			if (!skl[maps[item]] || !SKILL_D(maps[item])->valid_enable(item))
				ob->map_skill(item);
		}
	}
//      婚姻状态检查，yuj@sj 1999-09-13
	if (stringp(ob->query("marry/id")))
	{
		object marry_ob = new(LOADUSER_OB, ob->query("marry/id"));
		if (marry_ob->restore())
		{
			if (marry_ob->query("marry/id") == ob->query("id"))
				ob->set("marry/name", marry_ob->query("name"));
			else
				ob->delete("marry");
		}
		else
			ob->delete("marry");
		if (!ob->query("marry"))
			ob->add("divorce", 1);
		destruct(marry_ob);
	}
	"/cmds/usr/top"->add_rank(ob);
}
