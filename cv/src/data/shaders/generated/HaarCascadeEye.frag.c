/**
 * Haar Cascade
 * Usage: HaarCascadeEye();
 */

precision highp float;

varying vec2 v_texcoord;
uniform sampler2D ii;
uniform sampler2D ii2;
uniform float invArea;
uniform float iiMax;
uniform float ii2Max;
uniform float scale;
uniform vec2 pixelSizeIn;

float sample_ii(vec2 coord)
{
	vec4 value = texture2D(ii, coord);
	float r = value.r * 255.0;
	float g = value.g * 255.0;
	float b = value.b * 255.0;
	return (b * 65536.0 + g * 256.0 + r) / 16777215.0 * iiMax;
}

float rect_sum_ii(float x, float y, float w, float h, float weight)
{
	vec2 topLeft = v_texcoord + vec2(x * scale * pixelSizeIn.x, y * scale * pixelSizeIn.y);
	vec2 topRight = topLeft + vec2(w * scale * pixelSizeIn.x, 0.0);
	vec2 bottomLeft = topLeft + vec2(0.0, h * scale * pixelSizeIn.y);
	vec2 bottomRight = bottomLeft + vec2(w * scale * pixelSizeIn.x, 0.0);

	return weight * (sample_ii(bottomRight) + 
		sample_ii(topLeft) - sample_ii(topRight) - sample_ii(bottomLeft));
}

float sample_ii2(vec2 coord)
{
	vec4 value = texture2D(ii2, coord);
	float r = value.r * 255.0;
	float g = value.g * 255.0;
	float b = value.b * 255.0;
	return (b * 65536.0 + g * 256.0 + r) / 16777215.0 * ii2Max;
}

float rect_sum_ii2(float x, float y, float w, float h, float weight)
{
	vec2 topLeft = v_texcoord + vec2(x * scale * pixelSizeIn.x, y * scale * pixelSizeIn.y);
	vec2 topRight = topLeft + vec2(w * scale * pixelSizeIn.x, 0.0);
	vec2 bottomLeft = topLeft + vec2(0.0, h * scale * pixelSizeIn.y);
	vec2 bottomRight = bottomLeft + vec2(w * scale * pixelSizeIn.x, 0.0);

	return weight * (sample_ii2(bottomRight) + 
		sample_ii2(topLeft) - sample_ii2(topRight) - sample_ii2(bottomLeft));
}

int HaarCascadeEye_stage0(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 20.0, 12.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 20.0, 6.0, 2.0);
	if(sum < 0.12963959574699402 * factor)
		stage_sum += -0.7730420827865601;
	else
		stage_sum += 0.6835014820098877;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 1.0, 4.0, 15.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 4.0, 5.0, 3.0);
	if(sum < -0.046326808631420135 * factor)
		stage_sum += 0.5735275149345398;
	else
		stage_sum += -0.49097689986228943;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 10.0, 9.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 3.0, 2.0, 3.0);
	if(sum < -0.016173090785741806 * factor)
		stage_sum += 0.6025434136390686;
	else
		stage_sum += -0.3161070942878723;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 10.0, 9.0, -1.0);
	sum += rect_sum_ii(7.0, 3.0, 10.0, 3.0, 3.0);
	if(sum < -0.045828841626644135 * factor)
		stage_sum += 0.6417754888534546;
	else
		stage_sum += -0.15545040369033813;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 2.0, 2.0, 18.0, -1.0);
	sum += rect_sum_ii(12.0, 8.0, 2.0, 6.0, 3.0);
	if(sum < -0.0537596195936203 * factor)
		stage_sum += 0.5421931743621826;
	else
		stage_sum += -0.2048082947731018;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 9.0, 8.0, 3.0, 2.0);
	if(sum < 0.03417119011282921 * factor)
		stage_sum += -0.2338819056749344;
	else
		stage_sum += 0.4841090142726898;


	if(stage_sum > -1.4562760591506958)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage1(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 0.0, 17.0, 18.0, -1.0);
	sum += rect_sum_ii(2.0, 6.0, 17.0, 6.0, 3.0);
	if(sum < -0.2172762006521225 * factor)
		stage_sum += 0.7109889984130859;
	else
		stage_sum += -0.5936073064804077;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 10.0, 1.0, 8.0, -1.0);
	sum += rect_sum_ii(10.0, 14.0, 1.0, 4.0, 2.0);
	if(sum < 0.012071969918906689 * factor)
		stage_sum += -0.2824048101902008;
	else
		stage_sum += 0.5901355147361755;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 10.0, 9.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 10.0, 3.0, 2.0, 3.0);
	if(sum < -0.01785413920879364 * factor)
		stage_sum += 0.5313752293586731;
	else
		stage_sum += -0.22758960723876953;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 1.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 3.0, 6.0, 2.0, 3.0);
	if(sum < 0.02233361080288887 * factor)
		stage_sum += -0.17556099593639374;
	else
		stage_sum += 0.633561372756958;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 1.0, 15.0, 9.0, -1.0);
	sum += rect_sum_ii(3.0, 4.0, 15.0, 3.0, 3.0);
	if(sum < -0.091420017182827 * factor)
		stage_sum += 0.6156309247016907;
	else
		stage_sum += -0.16899530589580536;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 3.0, 9.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 5.0, 9.0, 2.0, 3.0);
	if(sum < 0.028973650187253952 * factor)
		stage_sum += -0.12250079959630966;
	else
		stage_sum += 0.7440117001533508;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 17.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 17.0, 2.0, 3.0, 3.0);
	if(sum < 0.007820346392691135 * factor)
		stage_sum += 0.16974370181560516;
	else
		stage_sum += -0.6544165015220642;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 10.0, 9.0, 1.0, -1.0);
	sum += rect_sum_ii(12.0, 10.0, 3.0, 1.0, 3.0);
	if(sum < 0.020340489223599434 * factor)
		stage_sum += -0.1255664974451065;
	else
		stage_sum += 0.8271045088768005;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 6.0, 11.0, -1.0);
	sum += rect_sum_ii(3.0, 7.0, 2.0, 11.0, 3.0);
	if(sum < -0.01192614994943142 * factor)
		stage_sum += 0.3860568106174469;
	else
		stage_sum += -0.2099234014749527;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 18.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(10.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < -0.000972811016254127 * factor)
		stage_sum += -0.6376119256019592;
	else
		stage_sum += 0.12952390313148499;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 16.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 17.0, 1.0, 1.0, 2.0);
	if(sum < 0.000018322050891583785 * factor)
		stage_sum += -0.34631478786468506;
	else
		stage_sum += 0.2292426973581314;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 17.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 17.0, 2.0, 3.0, 3.0);
	if(sum < -0.008085441775619984 * factor)
		stage_sum += -0.6366580128669739;
	else
		stage_sum += 0.13078659772872925;


	if(stage_sum > -1.2550230026245117)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage2(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 0.0, 5.0, 18.0, -1.0);
	sum += rect_sum_ii(8.0, 6.0, 5.0, 6.0, 3.0);
	if(sum < -0.11812269687652588 * factor)
		stage_sum += 0.6784452199935913;
	else
		stage_sum += -0.5004578232765198;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 9.0, 7.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 3.0, 7.0, 3.0);
	if(sum < -0.0343327596783638 * factor)
		stage_sum += 0.6718636155128479;
	else
		stage_sum += -0.3574487864971161;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 6.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(16.0, 6.0, 2.0, 10.0, 3.0);
	if(sum < -0.021530799567699432 * factor)
		stage_sum += 0.7222070097923279;
	else
		stage_sum += -0.18192419409751892;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 8.0, 9.0, 5.0, -1.0);
	sum += rect_sum_ii(12.0, 8.0, 3.0, 5.0, 3.0);
	if(sum < -0.02190997079014778 * factor)
		stage_sum += 0.6652938723564148;
	else
		stage_sum += -0.27510228753089905;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 9.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 3.0, 6.0, 3.0);
	if(sum < -0.028713539242744446 * factor)
		stage_sum += 0.6995570063591003;
	else
		stage_sum += -0.19615580141544342;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 7.0, 2.0, 6.0, 3.0);
	if(sum < -0.011467480100691319 * factor)
		stage_sum += 0.5926734805107117;
	else
		stage_sum += -0.22097350656986237;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 4.0, 18.0, -1.0);
	sum += rect_sum_ii(16.0, 6.0, 4.0, 6.0, 3.0);
	if(sum < -0.022611169144511223 * factor)
		stage_sum += 0.3448306918144226;
	else
		stage_sum += -0.3837955892086029;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 17.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 18.0, 3.0, 1.0, 3.0);
	if(sum < -0.0019308089977130294 * factor)
		stage_sum += -0.794457197189331;
	else
		stage_sum += 0.1562865972518921;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(17.0, 0.0, 1.0, 1.0, 2.0);
	if(sum < 0.00005641991083393805 * factor)
		stage_sum += -0.30896010994911194;
	else
		stage_sum += 0.35431089997291565;


	if(stage_sum > -1.372818946838379)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage3(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 20.0, 12.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 20.0, 6.0, 2.0);
	if(sum < 0.19886520504951477 * factor)
		stage_sum += -0.5286070108413696;
	else
		stage_sum += 0.3553672134876251;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 9.0, 8.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 3.0, 8.0, 3.0);
	if(sum < -0.036008939146995544 * factor)
		stage_sum += 0.42109689116477966;
	else
		stage_sum += -0.393489807844162;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 3.0, 12.0, 9.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 12.0, 3.0, 3.0);
	if(sum < -0.07756984978914261 * factor)
		stage_sum += 0.47991541028022766;
	else
		stage_sum += -0.2512216866016388;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 16.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(4.0, 17.0, 1.0, 1.0, 2.0);
	if(sum < 0.00008263085328508168 * factor)
		stage_sum += -0.38475489616394043;
	else
		stage_sum += 0.31849220395088196;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 10.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(19.0, 10.0, 1.0, 1.0, 2.0);
	if(sum < 0.00032773229759186506 * factor)
		stage_sum += -0.26427319645881653;
	else
		stage_sum += 0.3254724144935608;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 8.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(11.0, 8.0, 2.0, 5.0, 3.0);
	if(sum < -0.018574850633740425 * factor)
		stage_sum += 0.46736589074134827;
	else
		stage_sum += -0.15067270398139954;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(1.0, 0.0, 1.0, 1.0, 2.0);
	if(sum < -0.00007000876212259755 * factor)
		stage_sum += 0.2931315004825592;
	else
		stage_sum += -0.2536509931087494;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 8.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 2.0, 6.0, 3.0);
	if(sum < -0.018552130088210106 * factor)
		stage_sum += 0.4627366065979004;
	else
		stage_sum += -0.13148050010204315;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 7.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(13.0, 7.0, 2.0, 7.0, 3.0);
	if(sum < -0.013030420057475567 * factor)
		stage_sum += 0.41627219319343567;
	else
		stage_sum += -0.17751489579677582;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 14.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(19.0, 15.0, 1.0, 1.0, 2.0);
	if(sum < 0.00006569414108525962 * factor)
		stage_sum += -0.28035101294517517;
	else
		stage_sum += 0.2668074071407318;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 17.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 18.0, 1.0, 1.0, 2.0);
	if(sum < 0.00017005260451696813 * factor)
		stage_sum += -0.27027249336242676;
	else
		stage_sum += 0.23981650173664093;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 7.0, 2.0, 7.0, -1.0);
	sum += rect_sum_ii(15.0, 7.0, 1.0, 7.0, 2.0);
	if(sum < -0.0033129199873656034 * factor)
		stage_sum += 0.4441143870353699;
	else
		stage_sum += -0.14428889751434326;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 8.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 8.0, 1.0, 4.0, 2.0);
	if(sum < 0.0017583490116521716 * factor)
		stage_sum += -0.1612619012594223;
	else
		stage_sum += 0.42940768599510193;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 8.0, 12.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 10.0, 12.0, 2.0, 3.0);
	if(sum < -0.025194749236106873 * factor)
		stage_sum += 0.4068729877471924;
	else
		stage_sum += -0.18202580511569977;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0014031709870323539 * factor)
		stage_sum += 0.08475978672504425;
	else
		stage_sum += -0.8001856803894043;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 7.0, 1.0, 6.0, 3.0);
	if(sum < -0.007399172987788916 * factor)
		stage_sum += 0.5576609969139099;
	else
		stage_sum += -0.11843159794807434;


	if(stage_sum > -1.2879480123519897)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage4(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 9.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 3.0, 12.0, 3.0);
	if(sum < -0.029943080618977547 * factor)
		stage_sum += 0.3581081032752991;
	else
		stage_sum += -0.3848763108253479;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 2.0, 11.0, 12.0, -1.0);
	sum += rect_sum_ii(6.0, 6.0, 11.0, 4.0, 3.0);
	if(sum < -0.1256738007068634 * factor)
		stage_sum += 0.3931693136692047;
	else
		stage_sum += -0.30012258887290955;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 12.0, 5.0, 8.0, -1.0);
	sum += rect_sum_ii(1.0, 16.0, 5.0, 4.0, 2.0);
	if(sum < 0.0053635272197425365 * factor)
		stage_sum += -0.4390861988067627;
	else
		stage_sum += 0.19257010519504547;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 7.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(16.0, 7.0, 2.0, 7.0, 3.0);
	if(sum < -0.008097182027995586 * factor)
		stage_sum += 0.399066686630249;
	else
		stage_sum += -0.23407870531082153;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 8.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(12.0, 8.0, 2.0, 6.0, 3.0);
	if(sum < -0.016597909852862358 * factor)
		stage_sum += 0.4209528863430023;
	else
		stage_sum += -0.22674840688705444;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 18.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < -0.0020199299324303865 * factor)
		stage_sum += -0.7415673136711121;
	else
		stage_sum += 0.1260118931531906;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 17.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 18.0, 2.0, 1.0, 3.0);
	if(sum < -0.0015202340437099338 * factor)
		stage_sum += -0.7615460157394409;
	else
		stage_sum += 0.08637361228466034;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 7.0, 3.0);
	if(sum < -0.004966394044458866 * factor)
		stage_sum += 0.4218223989009857;
	else
		stage_sum += -0.17904919385910034;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 6.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(7.0, 6.0, 2.0, 8.0, 3.0);
	if(sum < -0.019207600504159927 * factor)
		stage_sum += 0.46894899010658264;
	else
		stage_sum += -0.14378750324249268;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 6.0, 6.0, 11.0, -1.0);
	sum += rect_sum_ii(4.0, 6.0, 2.0, 11.0, 3.0);
	if(sum < -0.012222680263221264 * factor)
		stage_sum += 0.3284207880496979;
	else
		stage_sum += -0.21802149713039398;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 10.0, 12.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 14.0, 12.0, 4.0, 2.0);
	if(sum < 0.05754866823554039 * factor)
		stage_sum += -0.3676880896091461;
	else
		stage_sum += 0.24357110261917114;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 17.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 17.0, 2.0, 3.0, 3.0);
	if(sum < -0.00957940798252821 * factor)
		stage_sum += -0.7224506735801697;
	else
		stage_sum += 0.06366456300020218;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 9.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 9.0, 1.0, 3.0, 3.0);
	if(sum < -0.002954574069008231 * factor)
		stage_sum += 0.35846439003944397;
	else
		stage_sum += -0.16696329414844513;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 8.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 1.0, 6.0, 3.0);
	if(sum < -0.004201799165457487 * factor)
		stage_sum += 0.390948086977005;
	else
		stage_sum += -0.12041790038347244;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 0.0, 2.0, 5.0, 3.0);
	if(sum < -0.013624990358948708 * factor)
		stage_sum += -0.5876771807670593;
	else
		stage_sum += 0.08840472996234894;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.00006285311246756464 * factor)
		stage_sum += -0.2634845972061157;
	else
		stage_sum += 0.21419279277324677;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 18.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < -0.0026782939676195383 * factor)
		stage_sum += -0.7839016914367676;
	else
		stage_sum += 0.08052696287631989;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 1.0, 11.0, 9.0, -1.0);
	sum += rect_sum_ii(4.0, 4.0, 11.0, 3.0, 3.0);
	if(sum < -0.07059717923402786 * factor)
		stage_sum += 0.41469261050224304;
	else
		stage_sum += -0.1398995965719223;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 1.0, 14.0, 9.0, -1.0);
	sum += rect_sum_ii(3.0, 4.0, 14.0, 3.0, 3.0);
	if(sum < 0.09209364652633667 * factor)
		stage_sum += -0.1305518001317978;
	else
		stage_sum += 0.5043578147888184;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(2.0, 9.0, 2.0, 4.0, 3.0);
	if(sum < -0.008800438605248928 * factor)
		stage_sum += 0.36609750986099243;
	else
		stage_sum += -0.14036649465560913;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 13.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(18.0, 14.0, 1.0, 1.0, 2.0);
	if(sum < 0.0000750809776945971 * factor)
		stage_sum += -0.29704439640045166;
	else
		stage_sum += 0.20702940225601196;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 5.0, 3.0, 11.0, -1.0);
	sum += rect_sum_ii(14.0, 5.0, 1.0, 11.0, 3.0);
	if(sum < -0.002987045096233487 * factor)
		stage_sum += 0.35615700483322144;
	else
		stage_sum += -0.15445969998836517;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 18.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 18.0, 4.0, 1.0, 2.0);
	sum += rect_sum_ii(4.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < -0.002644150983542204 * factor)
		stage_sum += -0.5435351729393005;
	else
		stage_sum += 0.10295110195875168;


	if(stage_sum > -1.2179850339889526)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage5(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 8.0, 12.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 4.0, 5.0, 3.0);
	if(sum < -0.047862470149993896 * factor)
		stage_sum += 0.41528239846229553;
	else
		stage_sum += -0.3418582081794739;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 11.0, 10.0, -1.0);
	sum += rect_sum_ii(4.0, 12.0, 11.0, 5.0, 2.0);
	if(sum < 0.08735053241252899 * factor)
		stage_sum += -0.38749781250953674;
	else
		stage_sum += 0.24204200506210327;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 9.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(16.0, 9.0, 2.0, 4.0, 3.0);
	if(sum < -0.016849499195814133 * factor)
		stage_sum += 0.5308247804641724;
	else
		stage_sum += -0.17282910645008087;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 7.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(3.0, 7.0, 3.0, 8.0, 2.0);
	if(sum < -0.028870029374957085 * factor)
		stage_sum += 0.35843509435653687;
	else
		stage_sum += -0.2240259051322937;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 16.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 17.0, 3.0, 1.0, 3.0);
	if(sum < 0.00256793899461627 * factor)
		stage_sum += 0.1499049961566925;
	else
		stage_sum += -0.6560940742492676;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 11.0, 12.0, 1.0, -1.0);
	sum += rect_sum_ii(11.0, 11.0, 4.0, 1.0, 3.0);
	if(sum < -0.02411665953695774 * factor)
		stage_sum += 0.5588967800140381;
	else
		stage_sum += -0.148102805018425;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 8.0, 9.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 8.0, 3.0, 4.0, 3.0);
	if(sum < -0.032826658338308334 * factor)
		stage_sum += 0.4646868109703064;
	else
		stage_sum += -0.10785529762506485;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 16.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 16.0, 2.0, 4.0, 3.0);
	if(sum < -0.015233060345053673 * factor)
		stage_sum += -0.7395442724227905;
	else
		stage_sum += 0.056236881762742996;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < -0.0003020951116923243 * factor)
		stage_sum += -0.4554882049560547;
	else
		stage_sum += 0.09706983715295792;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0007536510820500553 * factor)
		stage_sum += 0.09514729678630829;
	else
		stage_sum += -0.5489501953125;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 9.0, 4.0, 10.0, -1.0);
	sum += rect_sum_ii(4.0, 9.0, 2.0, 5.0, 2.0);
	sum += rect_sum_ii(6.0, 14.0, 2.0, 5.0, 2.0);
	if(sum < -0.010638950392603874 * factor)
		stage_sum += 0.40912970900535583;
	else
		stage_sum += -0.12308409810066223;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 8.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(6.0, 8.0, 2.0, 4.0, 3.0);
	if(sum < -0.007521783001720905 * factor)
		stage_sum += 0.40289148688316345;
	else
		stage_sum += -0.1604878008365631;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 2.0, 2.0, 18.0, -1.0);
	sum += rect_sum_ii(10.0, 8.0, 2.0, 6.0, 3.0);
	if(sum < -0.10677099972963333 * factor)
		stage_sum += 0.6175932288169861;
	else
		stage_sum += -0.07309118658304214;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 5.0, 4.0, 3.0, 2.0);
	sum += rect_sum_ii(4.0, 8.0, 4.0, 3.0, 2.0);
	if(sum < 0.016256919130682945 * factor)
		stage_sum += -0.13103680312633514;
	else
		stage_sum += 0.37453651428222656;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 0.0, 2.0, 5.0, 3.0);
	if(sum < -0.020679360255599022 * factor)
		stage_sum += -0.71402907371521;
	else
		stage_sum += 0.05239000916481018;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 0.0, 2.0, 14.0, -1.0);
	sum += rect_sum_ii(18.0, 7.0, 2.0, 7.0, 2.0);
	if(sum < 0.017052369192242622 * factor)
		stage_sum += 0.12822860479354858;
	else
		stage_sum += -0.3108068108558655;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 18.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 18.0, 2.0, 2.0, 2.0);
	if(sum < -0.0057122060097754 * factor)
		stage_sum += -0.605565071105957;
	else
		stage_sum += 0.08188475668430328;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 17.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 18.0, 6.0, 1.0, 3.0);
	if(sum < 0.000020851430235779844 * factor)
		stage_sum += -0.2681298851966858;
	else
		stage_sum += 0.14453840255737305;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 8.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(12.0, 8.0, 1.0, 5.0, 3.0);
	if(sum < 0.007928443141281605 * factor)
		stage_sum += -0.07879535108804703;
	else
		stage_sum += 0.5676258206367493;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.0025217379443347454 * factor)
		stage_sum += 0.37068629264831543;
	else
		stage_sum += -0.13620570302009583;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 0.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(13.0, 0.0, 2.0, 5.0, 3.0);
	if(sum < -0.022426199167966843 * factor)
		stage_sum += -0.6870499849319458;
	else
		stage_sum += 0.05106285959482193;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(3.0, 7.0, 2.0, 7.0, 3.0);
	if(sum < -0.007645144127309322 * factor)
		stage_sum += 0.23492220044136047;
	else
		stage_sum += -0.17905959486961365;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 13.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 1.0, 1.0, 3.0);
	if(sum < -0.0011175329564139247 * factor)
		stage_sum += -0.5986905097961426;
	else
		stage_sum += 0.07432443648576736;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 2.0, 9.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 4.0, 9.0, 2.0, 3.0);
	if(sum < 0.019212789833545685 * factor)
		stage_sum += -0.1570255011320114;
	else
		stage_sum += 0.2973746955394745;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 9.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 9.0, 1.0, 2.0);
	if(sum < 0.00562934298068285 * factor)
		stage_sum += -0.09976901859045029;
	else
		stage_sum += 0.4213027060031891;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 14.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 16.0, 3.0, 2.0, 3.0);
	if(sum < -0.00956718623638153 * factor)
		stage_sum += -0.6085879802703857;
	else
		stage_sum += 0.07350625842809677;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 11.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 11.0, 2.0, 4.0, 3.0);
	if(sum < 0.01121796015650034 * factor)
		stage_sum += -0.10320810228586197;
	else
		stage_sum += 0.41909849643707275;


	if(stage_sum > -1.2905240058898926)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage6(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 9.0, 9.0, 3.0, -1.0);
	sum += rect_sum_ii(9.0, 9.0, 3.0, 3.0, 3.0);
	if(sum < -0.017486440017819405 * factor)
		stage_sum += 0.3130728006362915;
	else
		stage_sum += -0.3368118107318878;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 9.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 2.0, 9.0, 2.0, 3.0);
	if(sum < 0.030714649707078934 * factor)
		stage_sum += -0.18766190111637115;
	else
		stage_sum += 0.5378080010414124;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 5.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 6.0, 2.0, 3.0);
	if(sum < -0.022188719362020493 * factor)
		stage_sum += 0.3663788139820099;
	else
		stage_sum += -0.1612481027841568;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 12.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(2.0, 12.0, 1.0, 1.0, 2.0);
	if(sum < -0.000050700771680567414 * factor)
		stage_sum += 0.2124571055173874;
	else
		stage_sum += -0.28444620966911316;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 10.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 10.0, 2.0, 2.0, 3.0);
	if(sum < -0.007017042022198439 * factor)
		stage_sum += 0.3954311013221741;
	else
		stage_sum += -0.1317359060049057;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 8.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(15.0, 8.0, 2.0, 6.0, 3.0);
	if(sum < -0.00685636093840003 * factor)
		stage_sum += 0.3037385940551758;
	else
		stage_sum += -0.20657819509506226;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 16.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 2.0, 4.0, 3.0);
	if(sum < -0.014129259623587132 * factor)
		stage_sum += -0.7650300860404968;
	else
		stage_sum += 0.09821318835020065;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 0.0, 9.0, 9.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 9.0, 3.0, 3.0);
	if(sum < -0.04791548103094101 * factor)
		stage_sum += 0.483073890209198;
	else
		stage_sum += -0.1300680935382843;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.000047032979637151584 * factor)
		stage_sum += -0.25216570496559143;
	else
		stage_sum += 0.24386680126190186;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0010221180273219943 * factor)
		stage_sum += 0.0688576027750969;
	else
		stage_sum += -0.6586114168167114;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 10.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 10.0, 1.0, 3.0, 3.0);
	if(sum < -0.002605610992759466 * factor)
		stage_sum += 0.4294202923774719;
	else
		stage_sum += -0.13022460043430328;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 14.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(10.0, 15.0, 1.0, 1.0, 2.0);
	if(sum < 0.00005450534081319347 * factor)
		stage_sum += -0.19288620352745056;
	else
		stage_sum += 0.2895849943161011;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 14.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 14.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(10.0, 15.0, 1.0, 1.0, 2.0);
	if(sum < -0.00006672115705441684 * factor)
		stage_sum += 0.3029071092605591;
	else
		stage_sum += -0.1985436975955963;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 19.0, 12.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 19.0, 6.0, 2.0);
	if(sum < 0.26281431317329407 * factor)
		stage_sum += -0.23293940722942352;
	else
		stage_sum += 0.23692460358142853;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 9.0, 14.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 3.0, 14.0, 3.0);
	if(sum < -0.02356966957449913 * factor)
		stage_sum += 0.1940104067325592;
	else
		stage_sum += -0.2848461866378784;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(14.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.003912017215043306 * factor)
		stage_sum += 0.5537897944450378;
	else
		stage_sum += -0.09566567838191986;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.00005078879985376261 * factor)
		stage_sum += -0.23912659287452698;
	else
		stage_sum += 0.21799489855766296;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 9.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(6.0, 9.0, 2.0, 3.0, 3.0);
	if(sum < -0.007873201742768288 * factor)
		stage_sum += 0.40697428584098816;
	else
		stage_sum += -0.12768040597438812;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 18.0, 5.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 19.0, 5.0, 1.0, 2.0);
	if(sum < -0.0016778609715402126 * factor)
		stage_sum += -0.5774465799331665;
	else
		stage_sum += 0.09732478857040405;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 8.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(8.0, 9.0, 1.0, 1.0, 2.0);
	if(sum < -0.0002683243073988706 * factor)
		stage_sum += 0.2902188003063202;
	else
		stage_sum += -0.1683126986026764;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 8.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(8.0, 9.0, 1.0, 1.0, 2.0);
	if(sum < 0.00007868718239478767 * factor)
		stage_sum += -0.1955157071352005;
	else
		stage_sum += 0.27720969915390015;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 10.0, 13.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 11.0, 13.0, 1.0, 2.0);
	if(sum < 0.012953500263392925 * factor)
		stage_sum += -0.0968383178114891;
	else
		stage_sum += 0.4032387137413025;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 8.0, 1.0, 9.0, -1.0);
	sum += rect_sum_ii(10.0, 11.0, 1.0, 3.0, 3.0);
	if(sum < -0.013043959625065327 * factor)
		stage_sum += 0.47198569774627686;
	else
		stage_sum += -0.08928754925727844;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 8.0, 2.0, 12.0, -1.0);
	sum += rect_sum_ii(15.0, 8.0, 1.0, 6.0, 2.0);
	sum += rect_sum_ii(16.0, 14.0, 1.0, 6.0, 2.0);
	if(sum < 0.0030261781066656113 * factor)
		stage_sum += -0.13623380661010742;
	else
		stage_sum += 0.3068627119064331;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 0.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(5.0, 0.0, 1.0, 5.0, 3.0);
	if(sum < -0.006043803878128529 * factor)
		stage_sum += -0.779541015625;
	else
		stage_sum += 0.057316310703754425;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 6.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(13.0, 6.0, 1.0, 7.0, 3.0);
	if(sum < -0.0022507249377667904 * factor)
		stage_sum += 0.3087705969810486;
	else
		stage_sum += -0.15006309747695923;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 16.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 16.0, 2.0, 4.0, 3.0);
	if(sum < 0.015826810151338577 * factor)
		stage_sum += 0.06455188989639282;
	else
		stage_sum += -0.7245556712150574;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 16.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(10.0, 16.0, 1.0, 1.0, 2.0);
	if(sum < 0.00006586450763279572 * factor)
		stage_sum += -0.17598840594291687;
	else
		stage_sum += 0.23210389912128448;


	if(stage_sum > -1.160048007965088)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage7(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 10.0, 9.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 10.0, 3.0, 2.0, 3.0);
	if(sum < -0.02785486914217472 * factor)
		stage_sum += 0.4551844894886017;
	else
		stage_sum += -0.18099910020828247;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 6.0, 15.0, 14.0, -1.0);
	sum += rect_sum_ii(0.0, 13.0, 15.0, 7.0, 2.0);
	if(sum < 0.12895040214061737 * factor)
		stage_sum += -0.5256553292274475;
	else
		stage_sum += 0.1618890017271042;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 1.0, 5.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 3.0, 5.0, 2.0, 3.0);
	if(sum < 0.024403180927038193 * factor)
		stage_sum += -0.14974960684776306;
	else
		stage_sum += 0.4235737919807434;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 9.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(4.0, 9.0, 1.0, 4.0, 3.0);
	if(sum < -0.0024458570405840874 * factor)
		stage_sum += 0.3294866979122162;
	else
		stage_sum += -0.17447690665721893;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 1.0, 6.0, 3.0);
	if(sum < -0.0035336529836058617 * factor)
		stage_sum += 0.4742664098739624;
	else
		stage_sum += -0.07361835986375809;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 16.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(17.0, 17.0, 1.0, 1.0, 2.0);
	if(sum < 0.00005135815081303008 * factor)
		stage_sum += -0.3042193055152893;
	else
		stage_sum += 0.15633270144462585;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 8.0, 6.0, 12.0, -1.0);
	sum += rect_sum_ii(11.0, 8.0, 2.0, 12.0, 3.0);
	if(sum < -0.016225680708885193 * factor)
		stage_sum += 0.23002180457115173;
	else
		stage_sum += -0.20359820127487183;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 10.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(8.0, 10.0, 2.0, 1.0, 3.0);
	if(sum < -0.004600700922310352 * factor)
		stage_sum += 0.40459269285202026;
	else
		stage_sum += -0.13485440611839294;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 17.0, 9.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 17.0, 3.0, 3.0, 3.0);
	if(sum < -0.021928999572992325 * factor)
		stage_sum += -0.6872448921203613;
	else
		stage_sum += 0.08068426698446274;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 18.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(14.0, 19.0, 6.0, 1.0, 2.0);
	if(sum < -0.002897121012210846 * factor)
		stage_sum += -0.6961960792541504;
	else
		stage_sum += 0.048545219004154205;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 3.0, 14.0, -1.0);
	sum += rect_sum_ii(10.0, 5.0, 1.0, 14.0, 3.0);
	if(sum < -0.0044074649922549725 * factor)
		stage_sum += 0.25166261196136475;
	else
		stage_sum += -0.16236649453639984;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 16.0, 9.0, 4.0, -1.0);
	sum += rect_sum_ii(11.0, 16.0, 3.0, 4.0, 3.0);
	if(sum < 0.028437169268727303 * factor)
		stage_sum += 0.06039426103234291;
	else
		stage_sum += -0.6674445867538452;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 4.0, 14.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 4.0, 7.0, 2.0);
	if(sum < 0.08321288228034973 * factor)
		stage_sum += 0.06435792148113251;
	else
		stage_sum += -0.5362604260444641;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 1.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 1.0, 2.0, 3.0, 3.0);
	if(sum < -0.012419329956173897 * factor)
		stage_sum += -0.708168625831604;
	else
		stage_sum += 0.0575266107916832;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.004699259996414185 * factor)
		stage_sum += 0.5125433206558228;
	else
		stage_sum += -0.08735080063343048;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.0007802580948919058 * factor)
		stage_sum += 0.26687660813331604;
	else
		stage_sum += -0.1796150952577591;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 1.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(7.0, 1.0, 2.0, 5.0, 3.0);
	if(sum < -0.019724339246749878 * factor)
		stage_sum += -0.6756373047828674;
	else
		stage_sum += 0.07294190675020218;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 18.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 19.0, 1.0, 1.0, 2.0);
	if(sum < 0.001026925048790872 * factor)
		stage_sum += 0.053919319063425064;
	else
		stage_sum += -0.5554018020629883;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 2.0, 6.0, 2.0, 3.0);
	if(sum < -0.02595718950033188 * factor)
		stage_sum += 0.5636252760887146;
	else
		stage_sum += -0.07189839333295822;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 18.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < -0.0012552699772641063 * factor)
		stage_sum += -0.5034663081169128;
	else
		stage_sum += 0.08969145268201828;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 3.0, 8.0, 12.0, -1.0);
	sum += rect_sum_ii(12.0, 7.0, 8.0, 4.0, 3.0);
	if(sum < -0.04997057840228081 * factor)
		stage_sum += 0.17685119807720184;
	else
		stage_sum += -0.22301959991455078;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 9.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 9.0, 1.0, 4.0, 3.0);
	if(sum < -0.002989961067214608 * factor)
		stage_sum += 0.391224205493927;
	else
		stage_sum += -0.10149750113487244;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 8.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(13.0, 8.0, 1.0, 5.0, 3.0);
	if(sum < 0.004854684229940176 * factor)
		stage_sum += -0.11770179867744446;
	else
		stage_sum += 0.4219093918800354;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 0.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(17.0, 0.0, 1.0, 1.0, 2.0);
	if(sum < 0.0001044886012095958 * factor)
		stage_sum += -0.17333979904651642;
	else
		stage_sum += 0.223444402217865;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(5.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.00005968926052446477 * factor)
		stage_sum += -0.23409630358219147;
	else
		stage_sum += 0.16558240354061127;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 2.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(10.0, 4.0, 3.0, 2.0, 3.0);
	if(sum < -0.013423919677734375 * factor)
		stage_sum += 0.43023818731307983;
	else
		stage_sum += -0.09972365200519562;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 17.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 18.0, 2.0, 1.0, 3.0);
	if(sum < 0.002258199965581298 * factor)
		stage_sum += 0.07272098958492279;
	else
		stage_sum += -0.5750101804733276;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 7.0, 1.0, 9.0, -1.0);
	sum += rect_sum_ii(12.0, 10.0, 1.0, 3.0, 3.0);
	if(sum < -0.012546280398964882 * factor)
		stage_sum += 0.36184579133987427;
	else
		stage_sum += -0.11457010358572006;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 3.0, 9.0, -1.0);
	sum += rect_sum_ii(8.0, 6.0, 1.0, 9.0, 3.0);
	if(sum < -0.002870576921850443 * factor)
		stage_sum += 0.28210538625717163;
	else
		stage_sum += -0.12367550283670425;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 13.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(17.0, 15.0, 3.0, 2.0, 3.0);
	if(sum < 0.019785640761256218 * factor)
		stage_sum += 0.0478767491877079;
	else
		stage_sum += -0.806662380695343;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 3.0, 8.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 1.0, 8.0, 3.0);
	if(sum < 0.004758893046528101 * factor)
		stage_sum += -0.1092538982629776;
	else
		stage_sum += 0.33746978640556335;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 0.0, 3.0, 5.0, -1.0);
	sum += rect_sum_ii(6.0, 0.0, 1.0, 5.0, 3.0);
	if(sum < -0.006997426971793175 * factor)
		stage_sum += -0.8029593825340271;
	else
		stage_sum += 0.045706700533628464;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 6.0, 9.0, 8.0, -1.0);
	sum += rect_sum_ii(7.0, 6.0, 3.0, 8.0, 3.0);
	if(sum < -0.013033480383455753 * factor)
		stage_sum += 0.18680439889431;
	else
		stage_sum += -0.176889106631279;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 9.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 9.0, 1.0, 3.0, 3.0);
	if(sum < -0.0013742579612880945 * factor)
		stage_sum += 0.27725479006767273;
	else
		stage_sum += -0.12809009850025177;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 18.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < 0.0027657810132950544 * factor)
		stage_sum += 0.09075894206762314;
	else
		stage_sum += -0.4259473979473114;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 10.0, 3.0, 10.0, -1.0);
	sum += rect_sum_ii(17.0, 15.0, 3.0, 5.0, 2.0);
	if(sum < 0.0002894184144679457 * factor)
		stage_sum += -0.388163298368454;
	else
		stage_sum += 0.089267797768116;


	if(stage_sum > -1.2257250547409058)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage8(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 9.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 9.0, 2.0, 4.0, 3.0);
	if(sum < -0.014469229616224766 * factor)
		stage_sum += 0.3750782907009125;
	else
		stage_sum += -0.24928289651870728;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 2.0, 10.0, 12.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 10.0, 4.0, 3.0);
	if(sum < -0.1331762969493866 * factor)
		stage_sum += 0.3016637861728668;
	else
		stage_sum += -0.2241407036781311;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 9.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 9.0, 2.0, 3.0, 3.0);
	if(sum < -0.010132160037755966 * factor)
		stage_sum += 0.3698559105396271;
	else
		stage_sum += -0.17850010097026825;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 7.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(12.0, 7.0, 1.0, 7.0, 3.0);
	if(sum < -0.007851118221879005 * factor)
		stage_sum += 0.46086761355400085;
	else
		stage_sum += -0.1293139010667801;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 8.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(14.0, 8.0, 2.0, 4.0, 3.0);
	if(sum < -0.014295839704573154 * factor)
		stage_sum += 0.44841429591178894;
	else
		stage_sum += -0.10226240009069443;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 8.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(16.0, 8.0, 2.0, 5.0, 3.0);
	if(sum < -0.005960694048553705 * factor)
		stage_sum += 0.279279887676239;
	else
		stage_sum += -0.15323829650878906;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 12.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 14.0, 2.0, 2.0, 2.0);
	if(sum < 0.010932769626379013 * factor)
		stage_sum += -0.15141740441322327;
	else
		stage_sum += 0.3988964855670929;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 15.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 16.0, 1.0, 1.0, 2.0);
	if(sum < 0.000050430990086169913 * factor)
		stage_sum += -0.22681570053100586;
	else
		stage_sum += 0.21644389629364014;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 7.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 7.0, 1.0, 4.0, 3.0);
	if(sum < -0.0058431681245565414 * factor)
		stage_sum += 0.45420148968696594;
	else
		stage_sum += -0.12587159872055054;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 0.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(12.0, 0.0, 2.0, 6.0, 3.0);
	if(sum < -0.02234620973467827 * factor)
		stage_sum += -0.6269019246101379;
	else
		stage_sum += 0.08240312337875366;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 6.0, 3.0, 8.0, -1.0);
	sum += rect_sum_ii(11.0, 6.0, 1.0, 8.0, 3.0);
	if(sum < -0.00488366698846221 * factor)
		stage_sum += 0.26359251141548157;
	else
		stage_sum += -0.1468663066625595;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 17.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 18.0, 1.0, 1.0, 2.0);
	if(sum < 0.00007550600275862962 * factor)
		stage_sum += -0.2450702041387558;
	else
		stage_sum += 0.16678880155086517;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 16.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 17.0, 1.0, 1.0, 3.0);
	if(sum < -0.0004902699729427695 * factor)
		stage_sum += -0.426499605178833;
	else
		stage_sum += 0.0899735614657402;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 11.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 12.0, 1.0, 1.0, 2.0);
	if(sum < 0.0014861579984426498 * factor)
		stage_sum += -0.1204025000333786;
	else
		stage_sum += 0.3009765148162842;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(5.0, 7.0, 2.0, 9.0, 3.0);
	if(sum < -0.011988339945673943 * factor)
		stage_sum += 0.278524786233902;
	else
		stage_sum += -0.12244340032339096;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 18.0, 9.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 18.0, 3.0, 1.0, 3.0);
	if(sum < 0.010502239689230919 * factor)
		stage_sum += 0.040452759712934494;
	else
		stage_sum += -0.7405040860176086;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 11.0, 4.0, 9.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 4.0, 3.0, 3.0);
	if(sum < -0.030963009223341942 * factor)
		stage_sum += -0.6284269094467163;
	else
		stage_sum += 0.04801376163959503;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 17.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 17.0, 2.0, 3.0, 3.0);
	if(sum < 0.01141452044248581 * factor)
		stage_sum += 0.0394052118062973;
	else
		stage_sum += -0.7167412042617798;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 6.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 2.0, 12.0, 3.0);
	if(sum < -0.012337000109255314 * factor)
		stage_sum += 0.19941329956054688;
	else
		stage_sum += -0.19274300336837769;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.005994226783514023 * factor)
		stage_sum += 0.5131816267967224;
	else
		stage_sum += -0.06165805831551552;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < -0.0011923230485990644 * factor)
		stage_sum += -0.72605299949646;
	else
		stage_sum += 0.05065272003412247;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 9.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 9.0, 2.0, 4.0, 3.0);
	if(sum < -0.0074582789093256 * factor)
		stage_sum += 0.29603078961372375;
	else
		stage_sum += -0.1175478994846344;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 1.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 1.0, 1.0, 2.0, 3.0);
	if(sum < 0.0027877509128302336 * factor)
		stage_sum += 0.045068711042404175;
	else
		stage_sum += -0.6953541040420532;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(2.0, 0.0, 1.0, 1.0, 2.0);
	if(sum < -0.0002250320976600051 * factor)
		stage_sum += 0.20047250390052795;
	else
		stage_sum += -0.15775249898433685;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 2.0, 14.0, -1.0);
	sum += rect_sum_ii(1.0, 0.0, 1.0, 7.0, 2.0);
	sum += rect_sum_ii(2.0, 7.0, 1.0, 7.0, 2.0);
	if(sum < -0.005036788992583752 * factor)
		stage_sum += 0.29299819469451904;
	else
		stage_sum += -0.11700499802827835;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 11.0, 8.0, -1.0);
	sum += rect_sum_ii(5.0, 9.0, 11.0, 4.0, 2.0);
	if(sum < 0.0747421607375145 * factor)
		stage_sum += -0.11392319947481155;
	else
		stage_sum += 0.30256620049476624;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 3.0, 5.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 5.0, 2.0, 3.0);
	if(sum < 0.020255519077181816 * factor)
		stage_sum += -0.10515890270471573;
	else
		stage_sum += 0.4067046046257019;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 9.0, 5.0, 10.0, -1.0);
	sum += rect_sum_ii(7.0, 14.0, 5.0, 5.0, 2.0);
	if(sum < 0.044214509427547455 * factor)
		stage_sum += -0.27631640434265137;
	else
		stage_sum += 0.12363869696855545;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 10.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 10.0, 1.0, 2.0, 2.0);
	if(sum < -0.0008725955849513412 * factor)
		stage_sum += 0.24355030059814453;
	else
		stage_sum += -0.13300949335098267;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 18.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 19.0, 8.0, 1.0, 2.0);
	if(sum < -0.0024453739169985056 * factor)
		stage_sum += -0.5386617183685303;
	else
		stage_sum += 0.062510646879673;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0000827253534225747 * factor)
		stage_sum += -0.20772209763526917;
	else
		stage_sum += 0.16270439326763153;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 2.0, 11.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 4.0, 11.0, 2.0, 3.0);
	if(sum < -0.036627110093832016 * factor)
		stage_sum += 0.3656840920448303;
	else
		stage_sum += -0.09033028036355972;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 3.0, 9.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 4.0, 9.0, 1.0, 3.0);
	if(sum < 0.0030996399000287056 * factor)
		stage_sum += -0.13183020055294037;
	else
		stage_sum += 0.2535429894924164;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 10.0, 2.0, 1.0, 2.0);
	if(sum < -0.0024709280114620924 * factor)
		stage_sum += -0.5685349702835083;
	else
		stage_sum += 0.05350543186068535;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 3.0, 2.0, 3.0);
	if(sum < -0.01411467045545578 * factor)
		stage_sum += -0.48599010705947876;
	else
		stage_sum += 0.0584852509200573;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(7.0, 8.0, 1.0, 1.0, 2.0);
	if(sum < 0.0008453726186417043 * factor)
		stage_sum += -0.0800936371088028;
	else
		stage_sum += 0.4026564955711365;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 6.0, 1.0, 6.0, 3.0);
	if(sum < -0.007109863217920065 * factor)
		stage_sum += 0.4470323920249939;
	else
		stage_sum += -0.06294743716716766;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 1.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(14.0, 1.0, 2.0, 4.0, 3.0);
	if(sum < -0.019125960767269135 * factor)
		stage_sum += -0.6642286777496338;
	else
		stage_sum += 0.049822770059108734;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 11.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(11.0, 11.0, 2.0, 8.0, 3.0);
	if(sum < -0.005077301058918238 * factor)
		stage_sum += 0.1737940013408661;
	else
		stage_sum += -0.16850599646568298;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 15.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(17.0, 16.0, 3.0, 1.0, 3.0);
	if(sum < -0.002919828984886408 * factor)
		stage_sum += -0.6011028289794922;
	else
		stage_sum += 0.057427939027547836;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 3.0, 9.0, -1.0);
	sum += rect_sum_ii(6.0, 9.0, 3.0, 3.0, 3.0);
	if(sum < -0.02490215003490448 * factor)
		stage_sum += 0.23397980630397797;
	else
		stage_sum += -0.11818459630012512;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 5.0, 4.0, 3.0, 2.0);
	sum += rect_sum_ii(4.0, 8.0, 4.0, 3.0, 2.0);
	if(sum < 0.02014777995646 * factor)
		stage_sum += -0.08945982158184052;
	else
		stage_sum += 0.3602440059185028;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 6.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 1.0, 1.0, 3.0);
	if(sum < 0.001759764039888978 * factor)
		stage_sum += 0.04945844039320946;
	else
		stage_sum += -0.6310262084007263;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 0.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(18.0, 0.0, 1.0, 6.0, 2.0);
	if(sum < 0.0013812039978802204 * factor)
		stage_sum += -0.15218059718608856;
	else
		stage_sum += 0.1897173970937729;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 17.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 17.0, 2.0, 3.0, 3.0);
	if(sum < -0.010904540307819843 * factor)
		stage_sum += -0.5809738039970398;
	else
		stage_sum += 0.04486272856593132;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 15.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 15.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(14.0, 16.0, 1.0, 1.0, 2.0);
	if(sum < 0.00007515717879869044 * factor)
		stage_sum += -0.13777349889278412;
	else
		stage_sum += 0.19543160498142242;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 0.0, 12.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 1.0, 12.0, 1.0, 3.0);
	if(sum < 0.003864977043122053 * factor)
		stage_sum += -0.10302229970693588;
	else
		stage_sum += 0.25374969840049744;


	if(stage_sum > -1.2863140106201172)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage9(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 3.0, 10.0, 9.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 10.0, 3.0, 3.0);
	if(sum < -0.10215889662504196 * factor)
		stage_sum += 0.41681259870529175;
	else
		stage_sum += -0.16655629873275757;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 9.0, 7.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 3.0, 7.0, 3.0);
	if(sum < -0.051939819008111954 * factor)
		stage_sum += 0.33023950457572937;
	else
		stage_sum += -0.20715710520744324;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 8.0, 9.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 8.0, 3.0, 6.0, 3.0);
	if(sum < -0.04271778091788292 * factor)
		stage_sum += 0.26093730330467224;
	else
		stage_sum += -0.16013890504837036;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 16.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 17.0, 6.0, 1.0, 2.0);
	if(sum < 0.00043890418601222336 * factor)
		stage_sum += -0.3475053012371063;
	else
		stage_sum += 0.1391891986131668;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 6.0, 7.0, 14.0, -1.0);
	sum += rect_sum_ii(12.0, 13.0, 7.0, 7.0, 2.0);
	if(sum < 0.024264389649033546 * factor)
		stage_sum += -0.4255205988883972;
	else
		stage_sum += 0.13578380644321442;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 7.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(15.0, 7.0, 2.0, 8.0, 3.0);
	if(sum < -0.023820599541068077 * factor)
		stage_sum += 0.3174980878829956;
	else
		stage_sum += -0.1665204018354416;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 10.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(4.0, 10.0, 2.0, 3.0, 3.0);
	if(sum < -0.007051818072795868 * factor)
		stage_sum += 0.3094717860221863;
	else
		stage_sum += -0.13338300585746765;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < -0.0006851715734228492 * factor)
		stage_sum += -0.6008226275444031;
	else
		stage_sum += 0.0877470001578331;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 1.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 2.0, 6.0, 1.0, 2.0);
	if(sum < 0.0053705149330198765 * factor)
		stage_sum += -0.12311449646949768;
	else
		stage_sum += 0.38333550095558167;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 0.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(6.0, 2.0, 6.0, 2.0, 2.0);
	if(sum < -0.013403539545834064 * factor)
		stage_sum += 0.3387736976146698;
	else
		stage_sum += -0.10140489786863327;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 18.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 18.0, 2.0, 2.0, 3.0);
	if(sum < -0.006685636006295681 * factor)
		stage_sum += -0.6119359731674194;
	else
		stage_sum += 0.04774022102355957;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 6.0, 5.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 7.0, 5.0, 1.0, 2.0);
	if(sum < -0.0042887418530881405 * factor)
		stage_sum += 0.2527579069137573;
	else
		stage_sum += -0.14434510469436646;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 7.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 7.0, 1.0, 6.0, 3.0);
	if(sum < -0.010876749642193317 * factor)
		stage_sum += 0.5477573275566101;
	else
		stage_sum += -0.05945548042654991;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 18.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(18.0, 18.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(19.0, 19.0, 1.0, 1.0, 2.0);
	if(sum < 0.0003788264002650976 * factor)
		stage_sum += 0.08341030031442642;
	else
		stage_sum += -0.4422636926174164;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 8.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(17.0, 8.0, 1.0, 7.0, 3.0);
	if(sum < -0.002455014968290925 * factor)
		stage_sum += 0.23330999910831451;
	else
		stage_sum += -0.1396448016166687;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 16.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 17.0, 2.0, 1.0, 3.0);
	if(sum < 0.0012721839593723416 * factor)
		stage_sum += 0.06048028916120529;
	else
		stage_sum += -0.4945608973503113;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 19.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 19.0, 2.0, 1.0, 3.0);
	if(sum < -0.004893315955996513 * factor)
		stage_sum += -0.6683326959609985;
	else
		stage_sum += 0.046218499541282654;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 5.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 6.0, 2.0, 3.0);
	if(sum < 0.026449989527463913 * factor)
		stage_sum += -0.07323536276817322;
	else
		stage_sum += 0.4442596137523651;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 10.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(0.0, 12.0, 2.0, 2.0, 2.0);
	if(sum < -0.003370607038959861 * factor)
		stage_sum += -0.4246433973312378;
	else
		stage_sum += 0.06867656111717224;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 9.0, 2.0, 3.0, 2.0);
	if(sum < -0.0029559480026364326 * factor)
		stage_sum += 0.16218039393424988;
	else
		stage_sum += -0.18222999572753906;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 10.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(3.0, 10.0, 2.0, 9.0, 3.0);
	if(sum < 0.0306199099868536 * factor)
		stage_sum += -0.058643341064453125;
	else
		stage_sum += 0.532636284828186;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 0.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 0.0, 2.0, 2.0, 3.0);
	if(sum < -0.009576590731739998 * factor)
		stage_sum += -0.6056268215179443;
	else
		stage_sum += 0.05334598943591118;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 1.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(15.0, 1.0, 1.0, 1.0, 2.0);
	if(sum < 0.00006637249316554517 * factor)
		stage_sum += -0.16680839657783508;
	else
		stage_sum += 0.19284160435199738;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 1.0, 4.0, -1.0);
	sum += rect_sum_ii(0.0, 10.0, 1.0, 2.0, 2.0);
	if(sum < 0.005097595043480396 * factor)
		stage_sum += 0.04411951079964638;
	else
		stage_sum += -0.574588418006897;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 6.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(15.0, 6.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(16.0, 7.0, 1.0, 1.0, 2.0);
	if(sum < 0.0003711271856445819 * factor)
		stage_sum += -0.11086399853229523;
	else
		stage_sum += 0.2310539036989212;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 5.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 1.0, 6.0, 3.0);
	if(sum < -0.008660758845508099 * factor)
		stage_sum += 0.40456289052963257;
	else
		stage_sum += -0.06244609132409096;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(19.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0008748915861360729 * factor)
		stage_sum += 0.06487514823675156;
	else
		stage_sum += -0.4487104117870331;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 10.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(8.0, 10.0, 1.0, 1.0, 3.0);
	if(sum < 0.0011120870476588607 * factor)
		stage_sum += -0.09386146068572998;
	else
		stage_sum += 0.30453911423683167;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 1.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(14.0, 1.0, 2.0, 6.0, 3.0);
	if(sum < -0.023837819695472717 * factor)
		stage_sum += -0.5888742804527283;
	else
		stage_sum += 0.04665942117571831;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 5.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(16.0, 5.0, 1.0, 1.0, 2.0);
	if(sum < 0.00022272899514064193 * factor)
		stage_sum += -0.14898599684238434;
	else
		stage_sum += 0.17701950669288635;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 2.0, 7.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 4.0, 7.0, 2.0, 2.0);
	if(sum < 0.0244674701243639 * factor)
		stage_sum += -0.05578960105776787;
	else
		stage_sum += 0.49208301305770874;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 0.0, 14.0, 15.0, -1.0);
	sum += rect_sum_ii(4.0, 5.0, 14.0, 5.0, 3.0);
	if(sum < -0.14239320158958435 * factor)
		stage_sum += 0.15192000567913055;
	else
		stage_sum += -0.18778899312019348;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 2.0, 6.0, 3.0);
	if(sum < -0.02012312039732933 * factor)
		stage_sum += 0.21780100464820862;
	else
		stage_sum += -0.12081900238990784;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.00011513679783092812 * factor)
		stage_sum += -0.16856589913368225;
	else
		stage_sum += 0.1645192950963974;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 16.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 16.0, 1.0, 2.0, 2.0);
	sum += rect_sum_ii(13.0, 18.0, 1.0, 2.0, 2.0);
	if(sum < -0.0027556740678846836 * factor)
		stage_sum += -0.6944203972816467;
	else
		stage_sum += 0.03944946825504303;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 13.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(11.0, 13.0, 1.0, 1.0, 2.0);
	if(sum < -0.00007584391278214753 * factor)
		stage_sum += 0.18941369652748108;
	else
		stage_sum += -0.15183840692043304;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 8.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 8.0, 1.0, 3.0, 3.0);
	if(sum < -0.0070697711780667305 * factor)
		stage_sum += 0.4706459939479828;
	else
		stage_sum += -0.05792761966586113;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 0.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(4.0, 0.0, 2.0, 8.0, 3.0);
	if(sum < -0.037393178790807724 * factor)
		stage_sum += -0.7589244842529297;
	else
		stage_sum += 0.034116048365831375;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 5.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 5.0, 3.0, 3.0, 2.0);
	sum += rect_sum_ii(6.0, 8.0, 3.0, 3.0, 2.0);
	if(sum < -0.015995610505342484 * factor)
		stage_sum += 0.30670469999313354;
	else
		stage_sum += -0.08752557635307312;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 8.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 8.0, 1.0, 3.0, 3.0);
	if(sum < -0.003118399064987898 * factor)
		stage_sum += 0.2619537115097046;
	else
		stage_sum += -0.09121488779783249;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 17.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 18.0, 4.0, 1.0, 2.0);
	if(sum < 0.001065136049874127 * factor)
		stage_sum += -0.17427560687065125;
	else
		stage_sum += 0.15277640521526337;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 16.0, 5.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 17.0, 5.0, 1.0, 2.0);
	if(sum < -0.0016029420075938106 * factor)
		stage_sum += 0.3561263084411621;
	else
		stage_sum += -0.07662999629974365;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 5.0, 3.0, 1.0, 3.0);
	if(sum < 0.004361990839242935 * factor)
		stage_sum += 0.04935697093605995;
	else
		stage_sum += -0.5922877192497253;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 3.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 2.0, 2.0, 3.0);
	if(sum < -0.010779909789562225 * factor)
		stage_sum += -0.6392217874526978;
	else
		stage_sum += 0.033204540610313416;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 4.0, 9.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 4.0, 3.0, 3.0, 3.0);
	if(sum < -0.004359086975455284 * factor)
		stage_sum += 0.16107389330863953;
	else
		stage_sum += -0.1522132009267807;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 13.0, 1.0, 4.0, -1.0);
	sum += rect_sum_ii(0.0, 15.0, 1.0, 2.0, 2.0);
	if(sum < 0.007459606975317001 * factor)
		stage_sum += 0.033172961324453354;
	else
		stage_sum += -0.7500774264335632;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 17.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 18.0, 8.0, 1.0, 3.0);
	if(sum < 0.008138544857501984 * factor)
		stage_sum += 0.026325279846787453;
	else
		stage_sum += -0.7173116207122803;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 1.0, 11.0, 6.0, -1.0);
	sum += rect_sum_ii(6.0, 3.0, 11.0, 2.0, 3.0);
	if(sum < -0.03333849087357521 * factor)
		stage_sum += 0.3353661000728607;
	else
		stage_sum += -0.07080359011888504;


	if(stage_sum > -1.1189440488815308)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage10(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 10.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 10.0, 2.0, 2.0, 3.0);
	if(sum < 0.019553979858756065 * factor)
		stage_sum += -0.10439720004796982;
	else
		stage_sum += 0.5312895178794861;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 8.0, 1.0, 12.0, -1.0);
	sum += rect_sum_ii(10.0, 14.0, 1.0, 6.0, 2.0);
	if(sum < 0.02212291955947876 * factor)
		stage_sum += -0.24747270345687866;
	else
		stage_sum += 0.20847250521183014;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(6.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < -0.004182938951998949 * factor)
		stage_sum += 0.3828943967819214;
	else
		stage_sum += -0.1471157968044281;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < -0.0008638172876089811 * factor)
		stage_sum += -0.6263288855552673;
	else
		stage_sum += 0.11993259936571121;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0007995861233212054 * factor)
		stage_sum += 0.09257347136735916;
	else
		stage_sum += -0.5516883134841919;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 8.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(14.0, 8.0, 1.0, 4.0, 3.0);
	if(sum < 0.009152757003903389 * factor)
		stage_sum += -0.07292980700731277;
	else
		stage_sum += 0.5551251173019409;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 5.0, 5.0, 4.0, -1.0);
	sum += rect_sum_ii(1.0, 7.0, 5.0, 2.0, 2.0);
	if(sum < -0.003938868176192045 * factor)
		stage_sum += 0.20196039974689484;
	else
		stage_sum += -0.20912039279937744;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 14.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(18.0, 15.0, 1.0, 1.0, 2.0);
	if(sum < 0.00014613410166930407 * factor)
		stage_sum += -0.278618186712265;
	else
		stage_sum += 0.13817410171031952;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 8.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(14.0, 8.0, 1.0, 4.0, 2.0);
	if(sum < -0.0031691689509898424 * factor)
		stage_sum += 0.36685898900032043;
	else
		stage_sum += -0.0763082429766655;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 6.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(12.0, 6.0, 2.0, 8.0, 3.0);
	if(sum < -0.022189389914274216 * factor)
		stage_sum += 0.39096599817276;
	else
		stage_sum += -0.10971540212631226;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 6.0, 10.0, -1.0);
	sum += rect_sum_ii(10.0, 6.0, 2.0, 10.0, 3.0);
	if(sum < -0.007452360820025206 * factor)
		stage_sum += 0.12838590145111084;
	else
		stage_sum += -0.2415986955165863;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 16.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(17.0, 17.0, 1.0, 1.0, 3.0);
	if(sum < 0.000779970025178045 * factor)
		stage_sum += 0.07197806984186172;
	else
		stage_sum += -0.43976500630378723;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 2.0, 10.0, -1.0);
	sum += rect_sum_ii(2.0, 7.0, 1.0, 10.0, 2.0);
	if(sum < -0.004678363911807537 * factor)
		stage_sum += 0.2156984955072403;
	else
		stage_sum += -0.14205920696258545;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 9.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(7.0, 9.0, 2.0, 3.0, 3.0);
	if(sum < -0.015188639983534813 * factor)
		stage_sum += 0.36458781361579895;
	else
		stage_sum += -0.08267592638731003;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 5.0, 12.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 5.0, 6.0, 2.0);
	if(sum < 0.0050619798712432384 * factor)
		stage_sum += -0.34380409121513367;
	else
		stage_sum += 0.09206823259592056;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 11.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 12.0, 1.0, 1.0, 3.0);
	if(sum < -0.0017351920250803232 * factor)
		stage_sum += -0.6172549724578857;
	else
		stage_sum += 0.049214478582143784;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 16.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 16.0, 2.0, 4.0, 3.0);
	if(sum < -0.012423450127243996 * factor)
		stage_sum += -0.5855895280838013;
	else
		stage_sum += 0.04611260071396828;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 6.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 8.0, 2.0, 2.0, 3.0);
	if(sum < -0.01303142961114645 * factor)
		stage_sum += -0.5971078872680664;
	else
		stage_sum += 0.040672458708286285;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 18.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(12.0, 18.0, 1.0, 1.0, 2.0);
	if(sum < -0.0012369629694148898 * factor)
		stage_sum += -0.6833416819572449;
	else
		stage_sum += 0.03315617889165878;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 1.0, 9.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 2.0, 9.0, 1.0, 2.0);
	if(sum < 0.006102210842072964 * factor)
		stage_sum += -0.0947292372584343;
	else
		stage_sum += 0.30102241039276123;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 1.0, 1.0, 1.0, 2.0);
	if(sum < 0.0006695284973829985 * factor)
		stage_sum += 0.08181686699390411;
	else
		stage_sum += -0.35196030139923096;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 9.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 9.0, 1.0, 3.0, 3.0);
	if(sum < -0.001797058037482202 * factor)
		stage_sum += 0.23718979954719543;
	else
		stage_sum += -0.11768709868192673;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 16.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 17.0, 1.0, 1.0, 3.0);
	if(sum < -0.0007107452838681638 * factor)
		stage_sum += -0.4476378858089447;
	else
		stage_sum += 0.05768248066306114;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(13.0, 10.0, 2.0, 1.0, 3.0);
	if(sum < -0.005912647116929293 * factor)
		stage_sum += 0.43425410985946655;
	else
		stage_sum += -0.06686857342720032;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 3.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 3.0, 2.0, 4.0, 2.0);
	if(sum < -0.003313214983791113 * factor)
		stage_sum += 0.18150010704994202;
	else
		stage_sum += -0.14180320501327515;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 2.0, 1.0, 18.0, -1.0);
	sum += rect_sum_ii(11.0, 8.0, 1.0, 6.0, 3.0);
	if(sum < -0.06081466004252434 * factor)
		stage_sum += 0.4722171127796173;
	else
		stage_sum += -0.06141063943505287;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 1.0, 5.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 5.0, 5.0, 4.0, 3.0);
	if(sum < -0.09671418368816376 * factor)
		stage_sum += 0.2768316864967346;
	else
		stage_sum += -0.09449003636837006;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 0.0, 8.0, 1.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 4.0, 1.0, 2.0);
	if(sum < 0.003907355014234781 * factor)
		stage_sum += -0.1227853000164032;
	else
		stage_sum += 0.21057400107383728;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 6.0, 3.0, 10.0, -1.0);
	sum += rect_sum_ii(9.0, 6.0, 1.0, 10.0, 3.0);
	if(sum < -0.009043186902999878 * factor)
		stage_sum += 0.35641568899154663;
	else
		stage_sum += -0.07780622690916061;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 2.0, 1.0, 6.0, -1.0);
	sum += rect_sum_ii(19.0, 4.0, 1.0, 2.0, 3.0);
	if(sum < -0.004880003165453672 * factor)
		stage_sum += -0.41034790873527527;
	else
		stage_sum += 0.06969437748193741;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 6.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(18.0, 7.0, 2.0, 1.0, 2.0);
	if(sum < -0.00435474282130599 * factor)
		stage_sum += -0.7301788926124573;
	else
		stage_sum += 0.03665515035390854;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 7.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 7.0, 1.0, 4.0, 3.0);
	if(sum < -0.009650062769651413 * factor)
		stage_sum += 0.5518112778663635;
	else
		stage_sum += -0.05316808074712753;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 0.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(7.0, 0.0, 2.0, 5.0, 3.0);
	if(sum < -0.017397310584783554 * factor)
		stage_sum += -0.5708423256874084;
	else
		stage_sum += 0.05021408945322037;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 3.0, 7.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 4.0, 7.0, 1.0, 3.0);
	if(sum < -0.006830432917922735 * factor)
		stage_sum += -0.46180281043052673;
	else
		stage_sum += 0.050202690064907074;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 6.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(2.0, 6.0, 1.0, 1.0, 2.0);
	if(sum < 0.00033255619928240776 * factor)
		stage_sum += -0.09536273032426834;
	else
		stage_sum += 0.2598375976085663;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 8.0, 2.0, 10.0, -1.0);
	sum += rect_sum_ii(4.0, 8.0, 1.0, 5.0, 2.0);
	sum += rect_sum_ii(5.0, 13.0, 1.0, 5.0, 2.0);
	if(sum < -0.0023100529797375202 * factor)
		stage_sum += 0.22872470319271088;
	else
		stage_sum += -0.1053353026509285;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 18.0, 18.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 18.0, 9.0, 1.0, 2.0);
	sum += rect_sum_ii(11.0, 19.0, 9.0, 1.0, 2.0);
	if(sum < -0.0075426651164889336 * factor)
		stage_sum += -0.5699051022529602;
	else
		stage_sum += 0.04886345937848091;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 7.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(2.0, 7.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(4.0, 9.0, 2.0, 2.0, 2.0);
	if(sum < -0.0052723060362041 * factor)
		stage_sum += 0.3514518141746521;
	else
		stage_sum += -0.08239010721445084;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 3.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(18.0, 3.0, 1.0, 4.0, 3.0);
	if(sum < -0.004857896827161312 * factor)
		stage_sum += -0.6041762232780457;
	else
		stage_sum += 0.0445394404232502;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 9.0, 2.0, 8.0, -1.0);
	sum += rect_sum_ii(16.0, 9.0, 1.0, 4.0, 2.0);
	sum += rect_sum_ii(17.0, 13.0, 1.0, 4.0, 2.0);
	if(sum < 0.001586731057614088 * factor)
		stage_sum += -0.10340909659862518;
	else
		stage_sum += 0.23282019793987274;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 7.0, 1.0, 6.0, -1.0);
	sum += rect_sum_ii(15.0, 9.0, 1.0, 2.0, 3.0);
	if(sum < -0.004742781165987253 * factor)
		stage_sum += 0.28490281105041504;
	else
		stage_sum += -0.09809049963951111;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 2.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(14.0, 3.0, 2.0, 1.0, 2.0);
	if(sum < -0.0013515240279957652 * factor)
		stage_sum += 0.2309643030166626;
	else
		stage_sum += -0.113618403673172;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 0.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(17.0, 1.0, 2.0, 1.0, 3.0);
	if(sum < 0.0022526069078594446 * factor)
		stage_sum += 0.0644783228635788;
	else
		stage_sum += -0.42205891013145447;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 18.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 18.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(17.0, 19.0, 1.0, 1.0, 2.0);
	if(sum < -0.0003803865984082222 * factor)
		stage_sum += -0.3807620108127594;
	else
		stage_sum += 0.06004329025745392;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 4.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 5.0, 4.0, 1.0, 3.0);
	if(sum < 0.004904392175376415 * factor)
		stage_sum += -0.07610499858856201;
	else
		stage_sum += 0.3323217034339905;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(4.0, 2.0, 4.0, 6.0, 2.0);
	if(sum < -0.009096967056393623 * factor)
		stage_sum += 0.14287790656089783;
	else
		stage_sum += -0.1688780039548874;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 14.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 16.0, 6.0, 2.0, 3.0);
	if(sum < -0.0069317929446697235 * factor)
		stage_sum += 0.27255409955978394;
	else
		stage_sum += -0.09287956357002258;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 15.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 16.0, 2.0, 1.0, 2.0);
	if(sum < 0.0011471060570329428 * factor)
		stage_sum += -0.15273059904575348;
	else
		stage_sum += 0.19702400267124176;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 1.0, 9.0, 4.0, -1.0);
	sum += rect_sum_ii(10.0, 1.0, 3.0, 4.0, 3.0);
	if(sum < -0.03766288980841637 * factor)
		stage_sum += -0.5932043790817261;
	else
		stage_sum += 0.04073860123753548;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 7.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 1.0, 7.0, 3.0);
	if(sum < -0.006816557142883539 * factor)
		stage_sum += 0.2549408972263336;
	else
		stage_sum += -0.09408196061849594;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 17.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 17.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(7.0, 18.0, 1.0, 1.0, 2.0);
	if(sum < 0.0006620556232519448 * factor)
		stage_sum += 0.046795718371868134;
	else
		stage_sum += -0.48454371094703674;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 6.0, 3.0, 9.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 1.0, 9.0, 3.0);
	if(sum < -0.004220255184918642 * factor)
		stage_sum += 0.24682149291038513;
	else
		stage_sum += -0.09467397630214691;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 10.0, 19.0, 10.0, -1.0);
	sum += rect_sum_ii(0.0, 15.0, 19.0, 5.0, 2.0);
	if(sum < -0.06898651272058487 * factor)
		stage_sum += -0.6651480197906494;
	else
		stage_sum += 0.03592639043927193;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 17.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 17.0, 2.0, 1.0, 3.0);
	if(sum < 0.006170760840177536 * factor)
		stage_sum += 0.02583331987261772;
	else
		stage_sum += -0.7268627285957336;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 12.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 12.0, 3.0, 3.0, 2.0);
	if(sum < 0.010536249727010727 * factor)
		stage_sum += -0.0818289965391159;
	else
		stage_sum += 0.29760798811912537;


	if(stage_sum > -1.1418989896774292)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage11(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 5.0, 18.0, 5.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 6.0, 5.0, 3.0);
	if(sum < -0.06275872886180878 * factor)
		stage_sum += 0.27899080514907837;
	else
		stage_sum += -0.2965610921382904;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 15.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(1.0, 17.0, 6.0, 2.0, 2.0);
	if(sum < 0.003451647935435176 * factor)
		stage_sum += -0.3463588058948517;
	else
		stage_sum += 0.2090384066104889;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 10.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(16.0, 10.0, 2.0, 6.0, 3.0);
	if(sum < -0.007869948633015156 * factor)
		stage_sum += 0.24144889414310455;
	else
		stage_sum += -0.19205570220947266;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < -0.0034624869003891945 * factor)
		stage_sum += -0.5915178060531616;
	else
		stage_sum += 0.12486449629068375;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 7.0, 6.0, 11.0, -1.0);
	sum += rect_sum_ii(3.0, 7.0, 2.0, 11.0, 3.0);
	if(sum < -0.009481876157224178 * factor)
		stage_sum += 0.1839154064655304;
	else
		stage_sum += -0.2485826015472412;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 17.0, 7.0, 2.0, -1.0);
	sum += rect_sum_ii(13.0, 18.0, 7.0, 1.0, 2.0);
	if(sum < 0.00023226840130519122 * factor)
		stage_sum += -0.33047258853912354;
	else
		stage_sum += 0.1099926009774208;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 14.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 15.0, 2.0, 1.0, 3.0);
	if(sum < 0.0018101120367646217 * factor)
		stage_sum += 0.09874401241540909;
	else
		stage_sum += -0.4963478147983551;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 0.0, 3.0, 2.0, 2.0);
	if(sum < -0.005442243069410324 * factor)
		stage_sum += 0.2934441864490509;
	else
		stage_sum += -0.13094750046730042;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 1.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(3.0, 1.0, 3.0, 3.0, 2.0);
	if(sum < 0.007414812222123146 * factor)
		stage_sum += -0.14762699604034424;
	else
		stage_sum += 0.3327716886997223;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 10.0, 2.0, 2.0, 3.0);
	if(sum < -0.015565140172839165 * factor)
		stage_sum += -0.6840490102767944;
	else
		stage_sum += 0.09987269341945648;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 2.0, 6.0, 14.0, -1.0);
	sum += rect_sum_ii(1.0, 2.0, 3.0, 7.0, 2.0);
	sum += rect_sum_ii(4.0, 9.0, 3.0, 7.0, 2.0);
	if(sum < 0.028720520436763763 * factor)
		stage_sum += -0.14833280444145203;
	else
		stage_sum += 0.3090257942676544;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 5.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(17.0, 5.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(18.0, 6.0, 1.0, 1.0, 2.0);
	if(sum < 0.00009668739221524447 * factor)
		stage_sum += -0.17431040108203888;
	else
		stage_sum += 0.21402959525585175;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 10.0, 9.0, 4.0, -1.0);
	sum += rect_sum_ii(14.0, 10.0, 3.0, 4.0, 3.0);
	if(sum < 0.052371058613061905 * factor)
		stage_sum += -0.07015685737133026;
	else
		stage_sum += 0.4922299087047577;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 9.0, 12.0, 4.0, -1.0);
	sum += rect_sum_ii(6.0, 9.0, 4.0, 4.0, 3.0);
	if(sum < -0.08648569136857986 * factor)
		stage_sum += 0.5075724720954895;
	else
		stage_sum += -0.07529421150684357;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 10.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(11.0, 10.0, 4.0, 2.0, 3.0);
	if(sum < -0.04216986894607544 * factor)
		stage_sum += 0.4568096101284027;
	else
		stage_sum += -0.0902199000120163;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 13.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 14.0, 1.0, 1.0, 2.0);
	if(sum < 0.000045369830331765115 * factor)
		stage_sum += -0.2653827965259552;
	else
		stage_sum += 0.16189539432525635;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 7.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 8.0, 4.0, 1.0, 3.0);
	if(sum < 0.0052918000146746635 * factor)
		stage_sum += 0.0748901516199112;
	else
		stage_sum += -0.540546715259552;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 16.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(19.0, 17.0, 1.0, 1.0, 3.0);
	if(sum < -0.0007551165181212127 * factor)
		stage_sum += -0.49261990189552307;
	else
		stage_sum += 0.058723948895931244;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 11.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(18.0, 12.0, 1.0, 1.0, 2.0);
	if(sum < 0.00007510813884437084 * factor)
		stage_sum += -0.21432100236415863;
	else
		stage_sum += 0.1407776027917862;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 7.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 7.0, 4.0, 1.0, 2.0);
	sum += rect_sum_ii(16.0, 8.0, 4.0, 1.0, 2.0);
	if(sum < 0.004998120944947004 * factor)
		stage_sum += -0.0905473381280899;
	else
		stage_sum += 0.35716068744659424;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 9.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(15.0, 9.0, 1.0, 4.0, 2.0);
	if(sum < -0.0014929979806765914 * factor)
		stage_sum += 0.2562345862388611;
	else
		stage_sum += -0.14229069650173187;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 2.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(14.0, 2.0, 3.0, 2.0, 2.0);
	sum += rect_sum_ii(17.0, 4.0, 3.0, 2.0, 2.0);
	if(sum < 0.0027239411137998104 * factor)
		stage_sum += -0.15649250149726868;
	else
		stage_sum += 0.2108871042728424;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(17.0, 0.0, 3.0, 1.0, 2.0);
	if(sum < 0.002221832051873207 * factor)
		stage_sum += -0.15072989463806152;
	else
		stage_sum += 0.2680186927318573;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 12.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(4.0, 12.0, 1.0, 1.0, 2.0);
	if(sum < -0.0007399307214654982 * factor)
		stage_sum += 0.29546990990638733;
	else
		stage_sum += -0.1069239005446434;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 2.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(18.0, 2.0, 1.0, 1.0, 3.0);
	if(sum < 0.0020113459322601557 * factor)
		stage_sum += 0.05061434954404831;
	else
		stage_sum += -0.7168337106704712;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 16.0, 18.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 16.0, 6.0, 2.0, 3.0);
	if(sum < 0.011452870443463326 * factor)
		stage_sum += -0.1271906942129135;
	else
		stage_sum += 0.24152779579162598;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 19.0, 8.0, 1.0, -1.0);
	sum += rect_sum_ii(6.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < -0.0010782170575112104 * factor)
		stage_sum += 0.24813009798526764;
	else
		stage_sum += -0.13461199402809143;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 17.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 18.0, 4.0, 1.0, 3.0);
	if(sum < 0.00334176910109818 * factor)
		stage_sum += 0.05357830971479416;
	else
		stage_sum += -0.5227416753768921;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 13.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(19.0, 14.0, 1.0, 1.0, 2.0);
	if(sum < 0.00006939865124877542 * factor)
		stage_sum += -0.21698740124702454;
	else
		stage_sum += 0.12812179327011108;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 16.0, 10.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 16.0, 5.0, 2.0, 2.0);
	sum += rect_sum_ii(14.0, 18.0, 5.0, 2.0, 2.0);
	if(sum < -0.0040982551872730255 * factor)
		stage_sum += 0.24401889741420746;
	else
		stage_sum += -0.11570589989423752;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 9.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 9.0, 1.0, 2.0, 2.0);
	sum += rect_sum_ii(13.0, 11.0, 1.0, 2.0, 2.0);
	if(sum < -0.0016289720078930259 * factor)
		stage_sum += 0.28261470794677734;
	else
		stage_sum += -0.10659469664096832;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 11.0, 1.0, 9.0, -1.0);
	sum += rect_sum_ii(19.0, 14.0, 1.0, 3.0, 3.0);
	if(sum < 0.01398485992103815 * factor)
		stage_sum += 0.042715899646282196;
	else
		stage_sum += -0.7364631295204163;


	if(stage_sum > -1.1255199909210205)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage12(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 6.0, 14.0, 14.0, -1.0);
	sum += rect_sum_ii(6.0, 13.0, 14.0, 7.0, 2.0);
	if(sum < 0.164165198802948 * factor)
		stage_sum += -0.4896030128002167;
	else
		stage_sum += 0.17607709765434265;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 17.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 18.0, 4.0, 1.0, 2.0);
	if(sum < 0.0008341306238435209 * factor)
		stage_sum += -0.2822043001651764;
	else
		stage_sum += 0.24199579656124115;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 3.0, 1.0, 1.0, 3.0);
	if(sum < -0.0017193210078403354 * factor)
		stage_sum += -0.714858889579773;
	else
		stage_sum += 0.08616221696138382;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 12.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 13.0, 1.0, 1.0, 3.0);
	if(sum < -0.001565495040267706 * factor)
		stage_sum += -0.7297238111495972;
	else
		stage_sum += 0.0940706729888916;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 15.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(15.0, 17.0, 4.0, 2.0, 2.0);
	if(sum < 0.0019124479731544852 * factor)
		stage_sum += -0.31187158823013306;
	else
		stage_sum += 0.18143390119075775;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 5.0, 18.0, 7.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 6.0, 7.0, 3.0);
	if(sum < -0.13512369990348816 * factor)
		stage_sum += 0.2957729995250702;
	else
		stage_sum += -0.22179250419139862;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 16.0, 5.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 17.0, 5.0, 1.0, 3.0);
	if(sum < -0.004030054900795221 * factor)
		stage_sum += -0.6659513711929321;
	else
		stage_sum += 0.08543101698160172;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 5.0, 2.0, 1.0, 3.0);
	if(sum < -0.002864046022295952 * factor)
		stage_sum += -0.6208636164665222;
	else
		stage_sum += 0.053106021136045456;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 6.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(1.0, 6.0, 1.0, 6.0, 2.0);
	if(sum < -0.0014065420255064964 * factor)
		stage_sum += 0.22346289455890656;
	else
		stage_sum += -0.20211009681224823;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 14.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 15.0, 4.0, 1.0, 3.0);
	if(sum < -0.0035820449702441692 * factor)
		stage_sum += -0.5403040051460266;
	else
		stage_sum += 0.06821361929178238;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 10.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 0.0, 5.0, 3.0, 2.0);
	sum += rect_sum_ii(5.0, 3.0, 5.0, 3.0, 2.0);
	if(sum < 0.04154447093605995 * factor)
		stage_sum += -0.06521584093570709;
	else
		stage_sum += 0.6210923194885254;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 2.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 2.0, 1.0, 6.0, 3.0);
	if(sum < -0.009170955047011375 * factor)
		stage_sum += -0.75553297996521;
	else
		stage_sum += 0.05264044925570488;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 0.0, 3.0, 10.0, -1.0);
	sum += rect_sum_ii(3.0, 0.0, 1.0, 10.0, 3.0);
	if(sum < 0.006155273877084255 * factor)
		stage_sum += 0.09093940258026123;
	else
		stage_sum += -0.4424613118171692;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 5.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 2.0, 1.0, 2.0);
	if(sum < -0.0010043520014733076 * factor)
		stage_sum += 0.242923304438591;
	else
		stage_sum += -0.18669790029525757;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 6.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(12.0, 8.0, 4.0, 2.0, 2.0);
	if(sum < 0.011519829742610455 * factor)
		stage_sum += -0.11763150244951248;
	else
		stage_sum += 0.36723458766937256;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 5.0, 7.0, 3.0, -1.0);
	sum += rect_sum_ii(13.0, 6.0, 7.0, 1.0, 3.0);
	if(sum < -0.008904073387384415 * factor)
		stage_sum += -0.4893133044242859;
	else
		stage_sum += 0.10897020250558853;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 13.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 14.0, 1.0, 1.0, 2.0);
	if(sum < 0.0005397367058321834 * factor)
		stage_sum += -0.21850399672985077;
	else
		stage_sum += 0.18489989638328552;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 16.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(18.0, 16.0, 2.0, 2.0, 2.0);
	if(sum < 0.0013727260520681739 * factor)
		stage_sum += -0.15072910487651825;
	else
		stage_sum += 0.2917312979698181;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 12.0, 4.0, 7.0, -1.0);
	sum += rect_sum_ii(18.0, 12.0, 2.0, 7.0, 2.0);
	if(sum < -0.010807390324771404 * factor)
		stage_sum += 0.4289745092391968;
	else
		stage_sum += -0.10280139744281769;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0012670770520344377 * factor)
		stage_sum += 0.07419215887784958;
	else
		stage_sum += -0.6420825123786926;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 9.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(19.0, 10.0, 1.0, 1.0, 3.0);
	if(sum < 0.002299112966284156 * factor)
		stage_sum += 0.04710027948021889;
	else
		stage_sum += -0.723352313041687;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 7.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(19.0, 7.0, 1.0, 6.0, 2.0);
	if(sum < 0.002718751085922122 * factor)
		stage_sum += -0.17086869478225708;
	else
		stage_sum += 0.23513509333133698;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 1.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(9.0, 1.0, 1.0, 4.0, 3.0);
	if(sum < -0.006661918014287949 * factor)
		stage_sum += -0.7897542715072632;
	else
		stage_sum += 0.045084670186042786;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 6.0, 9.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 2.0, 9.0, 3.0);
	if(sum < -0.04826664924621582 * factor)
		stage_sum += -0.6957991719245911;
	else
		stage_sum += 0.04197607934474945;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 2.0, 10.0, 2.0, -1.0);
	sum += rect_sum_ii(9.0, 2.0, 5.0, 2.0, 2.0);
	if(sum < 0.015214690007269382 * factor)
		stage_sum += -0.10818280279636383;
	else
		stage_sum += 0.36460620164871216;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 12.0, 8.0, 4.0, -1.0);
	sum += rect_sum_ii(2.0, 12.0, 4.0, 2.0, 2.0);
	sum += rect_sum_ii(6.0, 14.0, 4.0, 2.0, 2.0);
	if(sum < -0.006008013151586056 * factor)
		stage_sum += 0.30970990657806396;
	else
		stage_sum += -0.11359210312366486;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 7.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 5.0, 7.0, 1.0, 3.0);
	if(sum < 0.006612715777009726 * factor)
		stage_sum += 0.08066534250974655;
	else
		stage_sum += -0.46658530831336975;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 14.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 14.0, 1.0, 3.0, 3.0);
	if(sum < -0.007960701361298561 * factor)
		stage_sum += -0.8720194101333618;
	else
		stage_sum += 0.036774590611457825;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 3.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 3.0, 2.0, 3.0, 2.0);
	if(sum < 0.003884719917550683 * factor)
		stage_sum += -0.11666289716959;
	else
		stage_sum += 0.33070269227027893;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 2.0, 7.0, -1.0);
	sum += rect_sum_ii(2.0, 0.0, 1.0, 7.0, 2.0);
	if(sum < -0.001098881009966135 * factor)
		stage_sum += 0.2387257069349289;
	else
		stage_sum += -0.17656759917736053;


	if(stage_sum > -1.1729990243911743)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage13(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 16.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(15.0, 18.0, 4.0, 2.0, 2.0);
	if(sum < 0.0035903379321098328 * factor)
		stage_sum += -0.23688079416751862;
	else
		stage_sum += 0.24631640315055847;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 8.0, 12.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 10.0, 12.0, 2.0, 2.0);
	if(sum < 0.006481593009084463 * factor)
		stage_sum += -0.3137362003326416;
	else
		stage_sum += 0.18675759434700012;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 17.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(3.0, 18.0, 1.0, 1.0, 2.0);
	if(sum < 0.00007304840255528688 * factor)
		stage_sum += -0.2764435112476349;
	else
		stage_sum += 0.16496239602565765;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 1.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 1.0, 1.0, 4.0, 3.0);
	if(sum < -0.00385146401822567 * factor)
		stage_sum += -0.5601450800895691;
	else
		stage_sum += 0.11294739693403244;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 2.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(7.0, 2.0, 1.0, 4.0, 3.0);
	if(sum < 0.003858821000903845 * factor)
		stage_sum += 0.03984899818897247;
	else
		stage_sum += -0.5807185769081116;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 8.0, 9.0, 12.0, -1.0);
	sum += rect_sum_ii(9.0, 8.0, 3.0, 12.0, 3.0);
	if(sum < -0.024651220068335533 * factor)
		stage_sum += 0.16755010187625885;
	else
		stage_sum += -0.25343671441078186;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 1.0, 8.0, 6.0, -1.0);
	sum += rect_sum_ii(8.0, 3.0, 8.0, 2.0, 3.0);
	if(sum < 0.04724552109837532 * factor)
		stage_sum += -0.10662080347537994;
	else
		stage_sum += 0.3945198059082031;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 2.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(17.0, 2.0, 3.0, 3.0, 2.0);
	if(sum < 0.00659646512940526 * factor)
		stage_sum += -0.1774425059556961;
	else
		stage_sum += 0.2728019058704376;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 6.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 7.0, 1.0, 1.0, 3.0);
	if(sum < -0.0013177490327507257 * factor)
		stage_sum += -0.5427265167236328;
	else
		stage_sum += 0.04860658943653107;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 0.0, 10.0, 2.0, -1.0);
	sum += rect_sum_ii(15.0, 0.0, 5.0, 2.0, 2.0);
	if(sum < -0.005026170983910561 * factor)
		stage_sum += 0.2439424991607666;
	else
		stage_sum += -0.13143649697303772;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 0.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 0.0, 1.0, 2.0, 3.0);
	if(sum < 0.003463276894763112 * factor)
		stage_sum += 0.06904934346675873;
	else
		stage_sum += -0.7033624053001404;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 19.0, 10.0, 1.0, -1.0);
	sum += rect_sum_ii(8.0, 19.0, 5.0, 1.0, 2.0);
	if(sum < 0.0021692588925361633 * factor)
		stage_sum += -0.1328946053981781;
	else
		stage_sum += 0.2209852933883667;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 4.0, 7.0, 16.0, -1.0);
	sum += rect_sum_ii(0.0, 12.0, 7.0, 8.0, 2.0);
	if(sum < 0.029395870864391327 * factor)
		stage_sum += -0.2853052020072937;
	else
		stage_sum += 0.1354399025440216;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 16.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 17.0, 1.0, 1.0, 3.0);
	if(sum < -0.0009618144831620157 * factor)
		stage_sum += -0.580413818359375;
	else
		stage_sum += 0.037450648844242096;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 8.0, 12.0, 6.0, -1.0);
	sum += rect_sum_ii(11.0, 8.0, 4.0, 6.0, 3.0);
	if(sum < -0.1082099974155426 * factor)
		stage_sum += 0.39467281103134155;
	else
		stage_sum += -0.07865594327449799;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 9.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(16.0, 9.0, 2.0, 7.0, 3.0);
	if(sum < -0.01802486926317215 * factor)
		stage_sum += 0.27355629205703735;
	else
		stage_sum += -0.13415299355983734;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 17.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(14.0, 17.0, 2.0, 1.0, 3.0);
	if(sum < 0.006250984035432339 * factor)
		stage_sum += 0.023388059809803963;
	else
		stage_sum += -0.8008859157562256;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 1.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(17.0, 1.0, 1.0, 1.0, 3.0);
	if(sum < -0.0016088379779830575 * factor)
		stage_sum += -0.5676252245903015;
	else
		stage_sum += 0.041215669363737106;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 17.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 17.0, 4.0, 1.0, 2.0);
	sum += rect_sum_ii(4.0, 18.0, 4.0, 1.0, 2.0);
	if(sum < 0.0007756475242786109 * factor)
		stage_sum += -0.1489126980304718;
	else
		stage_sum += 0.1908618062734604;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 0.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(18.0, 0.0, 1.0, 1.0, 2.0);
	if(sum < 0.00008712233830010518 * factor)
		stage_sum += -0.15557530522346497;
	else
		stage_sum += 0.19428220391273499;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 15.0, 6.0, 5.0, -1.0);
	sum += rect_sum_ii(6.0, 15.0, 2.0, 5.0, 3.0);
	if(sum < -0.02075532078742981 * factor)
		stage_sum += -0.6300653219223022;
	else
		stage_sum += 0.03613438084721565;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 2.0, 8.0, 2.0, -1.0);
	sum += rect_sum_ii(7.0, 3.0, 8.0, 1.0, 2.0);
	if(sum < -0.0062931738793849945 * factor)
		stage_sum += 0.25609248876571655;
	else
		stage_sum += -0.10588269680738449;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 1.0, 8.0, 4.0, -1.0);
	sum += rect_sum_ii(4.0, 3.0, 8.0, 2.0, 2.0);
	if(sum < 0.010844149626791477 * factor)
		stage_sum += -0.10124850273132324;
	else
		stage_sum += 0.30322128534317017;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 19.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(6.0, 19.0, 1.0, 1.0, 2.0);
	if(sum < -0.00006375277735060081 * factor)
		stage_sum += 0.19111579656600952;
	else
		stage_sum += -0.13849230110645294;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 19.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(6.0, 19.0, 1.0, 1.0, 2.0);
	if(sum < 0.00006648096314165741 * factor)
		stage_sum += -0.15205250680446625;
	else
		stage_sum += 0.21706309914588928;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(16.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0013560829684138298 * factor)
		stage_sum += 0.04943178966641426;
	else
		stage_sum += -0.6427984237670898;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 11.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 11.0, 1.0, 3.0, 2.0);
	if(sum < -0.0009066255879588425 * factor)
		stage_sum += 0.17982010543346405;
	else
		stage_sum += -0.14044609665870667;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 19.0, 4.0, 1.0, -1.0);
	sum += rect_sum_ii(2.0, 19.0, 2.0, 1.0, 2.0);
	if(sum < 0.0010473709553480148 * factor)
		stage_sum += -0.10933549702167511;
	else
		stage_sum += 0.24265940487384796;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 18.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 18.0, 2.0, 2.0, 2.0);
	if(sum < -0.0010243969736620784 * factor)
		stage_sum += 0.2716268002986908;
	else
		stage_sum += -0.11820919811725616;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(2.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < -0.0012024149764329195 * factor)
		stage_sum += -0.701511025428772;
	else
		stage_sum += 0.03948989883065224;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 7.0, 11.0, 2.0, -1.0);
	sum += rect_sum_ii(5.0, 8.0, 11.0, 1.0, 2.0);
	if(sum < 0.007691164966672659 * factor)
		stage_sum += -0.09221891313791275;
	else
		stage_sum += 0.3104628920555115;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 2.0, 4.0, 10.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 4.0, 5.0, 2.0);
	if(sum < -0.13966549932956696 * factor)
		stage_sum += 0.6897938847541809;
	else
		stage_sum += -0.039706118404865265;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 2.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 3.0, 4.0, 1.0, 3.0);
	if(sum < 0.0021276050247251987 * factor)
		stage_sum += 0.09727761149406433;
	else
		stage_sum += -0.2884179949760437;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 19.0, 10.0, 1.0, -1.0);
	sum += rect_sum_ii(15.0, 19.0, 5.0, 1.0, 2.0);
	if(sum < -0.0027594310231506824 * factor)
		stage_sum += 0.24168670177459717;
	else
		stage_sum += -0.1127782016992569;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 17.0, 8.0, 3.0, -1.0);
	sum += rect_sum_ii(15.0, 17.0, 4.0, 3.0, 2.0);
	if(sum < 0.005223613232374191 * factor)
		stage_sum += -0.11430279910564423;
	else
		stage_sum += 0.24256780743598938;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 19.0, 3.0, 1.0, -1.0);
	sum += rect_sum_ii(9.0, 19.0, 1.0, 1.0, 3.0);
	if(sum < -0.0012590440455824137 * factor)
		stage_sum += -0.5967938899993896;
	else
		stage_sum += 0.047663960605859756;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 0.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(15.0, 0.0, 1.0, 4.0, 3.0);
	if(sum < -0.0037192099262028933 * factor)
		stage_sum += -0.464141309261322;
	else
		stage_sum += 0.052847690880298615;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 6.0, 4.0, 3.0, -1.0);
	sum += rect_sum_ii(10.0, 7.0, 4.0, 1.0, 3.0);
	if(sum < 0.005969615187495947 * factor)
		stage_sum += -0.07324428856372833;
	else
		stage_sum += 0.38743090629577637;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(0.0, 9.0, 3.0, 1.0, 2.0);
	if(sum < -0.005177672021090984 * factor)
		stage_sum += -0.7419322729110718;
	else
		stage_sum += 0.04049671068787575;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 12.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 14.0, 3.0, 2.0, 3.0);
	if(sum < 0.005003510043025017 * factor)
		stage_sum += -0.13888800144195557;
	else
		stage_sum += 0.18767620623111725;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 18.0, 1.0, 2.0, -1.0);
	sum += rect_sum_ii(1.0, 19.0, 1.0, 1.0, 2.0);
	if(sum < -0.0005201345775276423 * factor)
		stage_sum += -0.5494061708450317;
	else
		stage_sum += 0.049417849630117416;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 12.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(2.0, 12.0, 2.0, 4.0, 2.0);
	if(sum < 0.00531687680631876 * factor)
		stage_sum += -0.08248297870159149;
	else
		stage_sum += 0.3174056112766266;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 8.0, 6.0, 7.0, -1.0);
	sum += rect_sum_ii(3.0, 8.0, 2.0, 7.0, 3.0);
	if(sum < -0.01477458979934454 * factor)
		stage_sum += 0.20816099643707275;
	else
		stage_sum += -0.12115559726953506;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 8.0, 4.0, 5.0, -1.0);
	sum += rect_sum_ii(2.0, 8.0, 2.0, 5.0, 2.0);
	if(sum < -0.04141645133495331 * factor)
		stage_sum += -0.8243780732154846;
	else
		stage_sum += 0.03332918882369995;


	if(stage_sum > -1.036829948425293)
		return 1;
	else
		return 0;
}

int HaarCascadeEye_stage14(float factor)
{
	float sum;
	float stage_sum;

	sum = 0.0;
	sum += rect_sum_ii(19.0, 16.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(19.0, 17.0, 1.0, 1.0, 3.0);
	if(sum < 0.0009096252033486962 * factor)
		stage_sum += 0.0845799669623375;
	else
		stage_sum += -0.5611841082572937;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 5.0, 18.0, 6.0, -1.0);
	sum += rect_sum_ii(7.0, 5.0, 6.0, 6.0, 3.0);
	if(sum < -0.05613978952169418 * factor)
		stage_sum += 0.15341749787330627;
	else
		stage_sum += -0.2696731984615326;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 15.0, 4.0, 2.0, -1.0);
	sum += rect_sum_ii(2.0, 16.0, 4.0, 1.0, 2.0);
	if(sum < 0.0010292009683325887 * factor)
		stage_sum += -0.20489980280399323;
	else
		stage_sum += 0.2015317976474762;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 6.0, 2.0, 11.0, -1.0);
	sum += rect_sum_ii(19.0, 6.0, 1.0, 11.0, 2.0);
	if(sum < 0.00287830107845366 * factor)
		stage_sum += -0.17351140081882477;
	else
		stage_sum += 0.2129794955253601;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 12.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 14.0, 2.0, 2.0, 3.0);
	if(sum < -0.0074144392274320126 * factor)
		stage_sum += -0.5962486863136292;
	else
		stage_sum += 0.04707795009016991;

	sum = 0.0;
	sum += rect_sum_ii(12.0, 5.0, 3.0, 2.0, -1.0);
	sum += rect_sum_ii(12.0, 6.0, 3.0, 1.0, 2.0);
	if(sum < -0.0014831849839538336 * factor)
		stage_sum += 0.1902461051940918;
	else
		stage_sum += -0.1598639041185379;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 3.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 4.0, 2.0, 1.0, 3.0);
	if(sum < 0.0045968941412866116 * factor)
		stage_sum += 0.03144713118672371;
	else
		stage_sum += -0.6869434118270874;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 14.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(16.0, 16.0, 4.0, 2.0, 2.0);
	if(sum < 0.0024255330208688974 * factor)
		stage_sum += -0.23609359562397003;
	else
		stage_sum += 0.11036109924316406;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 8.0, 12.0, 5.0, -1.0);
	sum += rect_sum_ii(10.0, 8.0, 4.0, 5.0, 3.0);
	if(sum < -0.08495056629180908 * factor)
		stage_sum += 0.2310716062784195;
	else
		stage_sum += -0.1377653032541275;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 7.0, 2.0, 7.0, -1.0);
	sum += rect_sum_ii(14.0, 7.0, 1.0, 7.0, 2.0);
	if(sum < -0.005014568101614714 * factor)
		stage_sum += 0.3867610991001129;
	else
		stage_sum += -0.05621737986803055;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 8.0, 2.0, 6.0, -1.0);
	sum += rect_sum_ii(2.0, 8.0, 1.0, 6.0, 2.0);
	if(sum < -0.002148206112906337 * factor)
		stage_sum += 0.1819159984588623;
	else
		stage_sum += -0.17615699768066406;

	sum = 0.0;
	sum += rect_sum_ii(15.0, 0.0, 3.0, 7.0, -1.0);
	sum += rect_sum_ii(16.0, 0.0, 1.0, 7.0, 3.0);
	if(sum < -0.01039677020162344 * factor)
		stage_sum += -0.7535138130187988;
	else
		stage_sum += 0.024091970175504684;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 2.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(6.0, 2.0, 2.0, 2.0, 3.0);
	if(sum < -0.013466750271618366 * factor)
		stage_sum += -0.7211886048316956;
	else
		stage_sum += 0.034949369728565216;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 20.0, 9.0, -1.0);
	sum += rect_sum_ii(0.0, 12.0, 20.0, 3.0, 3.0);
	if(sum < -0.08443547785282135 * factor)
		stage_sum += -0.33792638778686523;
	else
		stage_sum += 0.07111381739377975;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 14.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 15.0, 2.0, 1.0, 2.0);
	if(sum < 0.00247714901342988 * factor)
		stage_sum += -0.11765109747648239;
	else
		stage_sum += 0.22541989386081696;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 5.0, 10.0, 4.0, -1.0);
	sum += rect_sum_ii(6.0, 7.0, 10.0, 2.0, 2.0);
	if(sum < 0.015828050673007965 * factor)
		stage_sum += -0.06953621655702591;
	else
		stage_sum += 0.313953697681427;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 1.0, 5.0, 9.0, -1.0);
	sum += rect_sum_ii(6.0, 4.0, 5.0, 3.0, 3.0);
	if(sum < 0.06491698324680328 * factor)
		stage_sum += -0.07504358887672424;
	else
		stage_sum += 0.4067733883857727;

	sum = 0.0;
	sum += rect_sum_ii(16.0, 18.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(16.0, 18.0, 1.0, 1.0, 2.0);
	sum += rect_sum_ii(17.0, 19.0, 1.0, 1.0, 2.0);
	if(sum < 0.00029652469675056636 * factor)
		stage_sum += 0.07395336031913757;
	else
		stage_sum += -0.3454400897026062;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 14.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(0.0, 16.0, 2.0, 2.0, 2.0);
	if(sum < 0.001312952022999525 * factor)
		stage_sum += -0.16909439861774445;
	else
		stage_sum += 0.15258370339870453;

	sum = 0.0;
	sum += rect_sum_ii(10.0, 8.0, 2.0, 5.0, -1.0);
	sum += rect_sum_ii(11.0, 8.0, 1.0, 5.0, 2.0);
	if(sum < -0.0058032129891216755 * factor)
		stage_sum += 0.3526014983654022;
	else
		stage_sum += -0.08344406634569168;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 7.0, 12.0, 7.0, -1.0);
	sum += rect_sum_ii(7.0, 7.0, 4.0, 7.0, 3.0);
	if(sum < -0.1479167938232422 * factor)
		stage_sum += 0.43004658818244934;
	else
		stage_sum += -0.05730992928147316;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 6.0, 6.0, -1.0);
	sum += rect_sum_ii(3.0, 0.0, 3.0, 6.0, 2.0);
	if(sum < -0.01658415049314499 * factor)
		stage_sum += 0.23432689905166626;
	else
		stage_sum += -0.10907640308141708;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(3.0, 0.0, 2.0, 4.0, 2.0);
	if(sum < 0.003018327057361603 * factor)
		stage_sum += -0.13600939512252808;
	else
		stage_sum += 0.26409289240837097;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 6.0, 8.0, -1.0);
	sum += rect_sum_ii(2.0, 0.0, 2.0, 8.0, 3.0);
	if(sum < -0.03647191822528839 * factor)
		stage_sum += -0.628097414970398;
	else
		stage_sum += 0.043545108288526535;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 2.0, 1.0, -1.0);
	sum += rect_sum_ii(1.0, 0.0, 1.0, 1.0, 2.0);
	if(sum < -0.00007311922672670335 * factor)
		stage_sum += 0.1647063046693802;
	else
		stage_sum += -0.16463780403137207;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 0.0, 3.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 1.0, 3.0, 1.0, 3.0);
	if(sum < -0.003671945072710514 * factor)
		stage_sum += -0.4742136001586914;
	else
		stage_sum += 0.04858691990375519;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 4.0, 2.0, 4.0, -1.0);
	sum += rect_sum_ii(5.0, 6.0, 2.0, 2.0, 2.0);
	if(sum < -0.004015117883682251 * factor)
		stage_sum += 0.18222180008888245;
	else
		stage_sum += -0.14097510278224945;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 10.0, 9.0, 1.0, -1.0);
	sum += rect_sum_ii(5.0, 10.0, 3.0, 1.0, 3.0);
	if(sum < 0.019948020577430725 * factor)
		stage_sum += -0.0697876587510109;
	else
		stage_sum += 0.3670746088027954;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(1.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.0007669943734072149 * factor)
		stage_sum += 0.055729299783706665;
	else
		stage_sum += -0.4458543062210083;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 17.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(0.0, 18.0, 2.0, 1.0, 3.0);
	if(sum < -0.0011806039838120341 * factor)
		stage_sum += -0.4687662124633789;
	else
		stage_sum += 0.04890222102403641;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 15.0, 16.0, 3.0, -1.0);
	sum += rect_sum_ii(8.0, 15.0, 8.0, 3.0, 2.0);
	if(sum < 0.015847349539399147 * factor)
		stage_sum += -0.12120209634304047;
	else
		stage_sum += 0.20566530525684357;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 5.0, 4.0, 1.0, -1.0);
	sum += rect_sum_ii(2.0, 5.0, 2.0, 1.0, 2.0);
	if(sum < -0.0011985700111836195 * factor)
		stage_sum += 0.2026209980249405;
	else
		stage_sum += -0.12823820114135742;

	sum = 0.0;
	sum += rect_sum_ii(1.0, 0.0, 6.0, 20.0, -1.0);
	sum += rect_sum_ii(3.0, 0.0, 2.0, 20.0, 3.0);
	if(sum < -0.10964959859848022 * factor)
		stage_sum += -0.8661919236183167;
	else
		stage_sum += 0.030351849272847176;

	sum = 0.0;
	sum += rect_sum_ii(2.0, 5.0, 4.0, 6.0, -1.0);
	sum += rect_sum_ii(2.0, 5.0, 2.0, 3.0, 2.0);
	sum += rect_sum_ii(4.0, 8.0, 2.0, 3.0, 2.0);
	if(sum < -0.009253260679543018 * factor)
		stage_sum += 0.29343119263648987;
	else
		stage_sum += -0.08536195009946823;

	sum = 0.0;
	sum += rect_sum_ii(9.0, 16.0, 6.0, 3.0, -1.0);
	sum += rect_sum_ii(11.0, 16.0, 2.0, 3.0, 3.0);
	if(sum < 0.014686530455946922 * factor)
		stage_sum += 0.03279862180352211;
	else
		stage_sum += -0.7755656242370605;

	sum = 0.0;
	sum += rect_sum_ii(11.0, 17.0, 6.0, 1.0, -1.0);
	sum += rect_sum_ii(14.0, 17.0, 3.0, 1.0, 2.0);
	if(sum < -0.0013514430029317737 * factor)
		stage_sum += 0.24426999688148499;
	else
		stage_sum += -0.11503250151872635;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 17.0, 15.0, 2.0, -1.0);
	sum += rect_sum_ii(8.0, 17.0, 5.0, 2.0, 3.0);
	if(sum < -0.004372809082269669 * factor)
		stage_sum += 0.21687670052051544;
	else
		stage_sum += -0.13984480500221252;

	sum = 0.0;
	sum += rect_sum_ii(18.0, 0.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(18.0, 1.0, 2.0, 1.0, 3.0);
	if(sum < 0.0034263390116393566 * factor)
		stage_sum += 0.04561422020196915;
	else
		stage_sum += -0.545677125453949;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 1.0, 7.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 3.0, 7.0, 2.0, 2.0);
	if(sum < -0.0038404068909585476 * factor)
		stage_sum += 0.14949500560760498;
	else
		stage_sum += -0.1506250947713852;

	sum = 0.0;
	sum += rect_sum_ii(13.0, 6.0, 4.0, 4.0, -1.0);
	sum += rect_sum_ii(13.0, 6.0, 2.0, 2.0, 2.0);
	sum += rect_sum_ii(15.0, 8.0, 2.0, 2.0, 2.0);
	if(sum < 0.0037988980766385794 * factor)
		stage_sum += -0.08730162680149078;
	else
		stage_sum += 0.25481531023979187;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 6.0, 3.0, 4.0, -1.0);
	sum += rect_sum_ii(17.0, 8.0, 3.0, 2.0, 2.0);
	if(sum < -0.0020094281062483788 * factor)
		stage_sum += 0.1725907027721405;
	else
		stage_sum += -0.14288470149040222;

	sum = 0.0;
	sum += rect_sum_ii(14.0, 9.0, 2.0, 2.0, -1.0);
	sum += rect_sum_ii(15.0, 9.0, 1.0, 2.0, 2.0);
	if(sum < -0.002437070943415165 * factor)
		stage_sum += 0.26848098635673523;
	else
		stage_sum += -0.08189821988344193;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 17.0, 1.0, 3.0, -1.0);
	sum += rect_sum_ii(17.0, 18.0, 1.0, 1.0, 3.0);
	if(sum < 0.001048539998009801 * factor)
		stage_sum += 0.046113260090351105;
	else
		stage_sum += -0.47243279218673706;

	sum = 0.0;
	sum += rect_sum_ii(3.0, 19.0, 8.0, 1.0, -1.0);
	sum += rect_sum_ii(7.0, 19.0, 4.0, 1.0, 2.0);
	if(sum < 0.00174607802182436 * factor)
		stage_sum += -0.11030430346727371;
	else
		stage_sum += 0.20379729568958282;

	sum = 0.0;
	sum += rect_sum_ii(0.0, 9.0, 3.0, 6.0, -1.0);
	sum += rect_sum_ii(0.0, 12.0, 3.0, 3.0, 2.0);
	if(sum < 0.005860862787812948 * factor)
		stage_sum += -0.15619659423828125;
	else
		stage_sum += 0.1592743992805481;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 7.0, 15.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 7.0, 5.0, 5.0, 3.0);
	if(sum < -0.02772497944533825 * factor)
		stage_sum += 0.11349119991064072;
	else
		stage_sum += -0.21885140240192413;

	sum = 0.0;
	sum += rect_sum_ii(6.0, 9.0, 9.0, 5.0, -1.0);
	sum += rect_sum_ii(9.0, 9.0, 3.0, 5.0, 3.0);
	if(sum < 0.047080639749765396 * factor)
		stage_sum += -0.04168872907757759;
	else
		stage_sum += 0.5363004803657532;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 1.0, 6.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 1.0, 2.0, 2.0, 3.0);
	if(sum < -0.007928377017378807 * factor)
		stage_sum += -0.5359513163566589;
	else
		stage_sum += 0.04423750936985016;

	sum = 0.0;
	sum += rect_sum_ii(4.0, 0.0, 12.0, 2.0, -1.0);
	sum += rect_sum_ii(10.0, 0.0, 6.0, 2.0, 2.0);
	if(sum < -0.012880540452897549 * factor)
		stage_sum += 0.2323794960975647;
	else
		stage_sum += -0.10246250033378601;

	sum = 0.0;
	sum += rect_sum_ii(7.0, 0.0, 10.0, 3.0, -1.0);
	sum += rect_sum_ii(12.0, 0.0, 5.0, 3.0, 2.0);
	if(sum < 0.02360476925969124 * factor)
		stage_sum += -0.08829143643379211;
	else
		stage_sum += 0.3056105971336365;

	sum = 0.0;
	sum += rect_sum_ii(5.0, 0.0, 9.0, 6.0, -1.0);
	sum += rect_sum_ii(5.0, 2.0, 9.0, 2.0, 3.0);
	if(sum < 0.0159022007137537 * factor)
		stage_sum += -0.12238109856843948;
	else
		stage_sum += 0.17849120497703552;

	sum = 0.0;
	sum += rect_sum_ii(8.0, 3.0, 6.0, 4.0, -1.0);
	sum += rect_sum_ii(8.0, 5.0, 6.0, 2.0, 2.0);
	if(sum < 0.007993949577212334 * factor)
		stage_sum += -0.08372900635004044;
	else
		stage_sum += 0.3231959044933319;

	sum = 0.0;
	sum += rect_sum_ii(17.0, 4.0, 2.0, 3.0, -1.0);
	sum += rect_sum_ii(17.0, 5.0, 2.0, 1.0, 3.0);
	if(sum < 0.005710086785256863 * factor)
		stage_sum += 0.03847920894622803;
	else
		stage_sum += -0.6813815236091614;


	if(stage_sum > -1.0492420196533203)
		return 1;
	else
		return 0;
}

vec4 HaarCascadeEye()
{
	float invArea = 1.0 / (scale * 20.0 * scale * 20.0);
	float mean = rect_sum_ii(v_texcoord.x, v_texcoord.y, 20.0, 20.0, invArea);
	float variance = rect_sum_ii2(v_texcoord.x, v_texcoord.y, 20.0, 20.0, invArea) - (mean * mean);
	float std = sqrt(variance);
	if(HaarCascadeEye_stage0(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage1(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage2(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage3(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage4(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage5(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage6(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage7(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage8(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage9(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage10(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage11(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage12(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage13(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	if(HaarCascadeEye_stage14(std / invArea) == 0) return vec4(0.0, 0.0, 0.0, 1.0);
	return vec4(1.0, 1.0, 1.0, 1.0);
}

void main()
{
	gl_FragColor = HaarCascadeEye();
}
