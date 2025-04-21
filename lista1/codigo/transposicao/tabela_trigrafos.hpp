#ifndef TABELA_TRIGRAFOS_HPP
#define TABELA_TRIGRAFOS_HPP

inline double trigrafos[26][26][26] = {};

//Lista dos 40 trigrafos mais frequentes e respectivas ocorrencias por 1000
inline void inicializar_trigrafos() {
    trigrafos['q'-'a']['u'-'a']['e'-'a'] = 7.229;
    trigrafos['e'-'a']['n'-'a']['t'-'a'] = 7.023;
    trigrafos['n'-'a']['t'-'a']['e'-'a'] = 5.508;
    trigrafos['a'-'a']['d'-'a']['o'-'a'] = 5.116;
    trigrafos['a'-'a']['d'-'a']['e'-'a'] = 5.004;
    trigrafos['o'-'a']['d'-'a']['e'-'a'] = 4.543;
    trigrafos['a'-'a']['r'-'a']['a'-'a'] = 4.537;
    trigrafos['e'-'a']['s'-'a']['t'-'a'] = 4.390;
    trigrafos['r'-'a']['e'-'a']['s'-'a'] = 4.308;
    trigrafos['c'-'a']['o'-'a']['n'-'a'] = 4.173;
    trigrafos['c'-'a']['o'-'a']['m'-'a'] = 4.095;
    trigrafos['s'-'a']['t'-'a']['a'-'a'] = 3.095;
    trigrafos['d'-'a']['o'-'a']['s'-'a'] = 3.808;
    trigrafos['c'-'a']['a'-'a']['o'-'a'] = 3.797;
    trigrafos['p'-'a']['a'-'a']['r'-'a'] = 3.629;
    trigrafos['a'-'a']['c'-'a']['a'-'a'] = 3.555;
    trigrafos['m'-'a']['e'-'a']['n'-'a'] = 3.465;
    trigrafos['s'-'a']['d'-'a']['e'-'a'] = 3.345;
    trigrafos['i'-'a']['c'-'a']['a'-'a'] = 3.305;
    trigrafos['e'-'a']['s'-'a']['e'-'a'] = 3.187;
    trigrafos['a'-'a']['c'-'a']['o'-'a'] = 3.154;
    trigrafos['a'-'a']['d'-'a']['a'-'a'] = 3.145;
    trigrafos['p'-'a']['o'-'a']['r'-'a'] = 3.139;
    trigrafos['n'-'a']['t'-'a']['o'-'a'] = 3.114;
    trigrafos['o'-'a']['s'-'a']['e'-'a'] = 3.082;
    trigrafos['d'-'a']['e'-'a']['s'-'a'] = 3.051;
    trigrafos['a'-'a']['s'-'a']['e'-'a'] = 2.776;
    trigrafos['e'-'a']['r'-'a']['a'-'a'] = 2.718;
    trigrafos['o'-'a']['e'-'a']['s'-'a'] = 2.660;
    trigrafos['u'-'a']['m'-'a']['a'-'a'] = 2.573;
    trigrafos['t'-'a']['r'-'a']['a'-'a'] = 2.566;
    trigrafos['i'-'a']['d'-'a']['a'-'a'] = 2.555;
    trigrafos['d'-'a']['a'-'a']['d'-'a'] = 2.484;
    trigrafos['a'-'a']['n'-'a']['t'-'a'] = 2.454;
    trigrafos['a'-'a']['r'-'a']['e'-'a'] = 2.430;
    trigrafos['o'-'a']['n'-'a']['t'-'a'] = 2.405;
    trigrafos['p'-'a']['r'-'a']['e'-'a'] = 2.404;
    trigrafos['i'-'a']['s'-'a']['t'-'a'] = 2.391;
    trigrafos['t'-'a']['e'-'a']['r'-'a'] = 2.389;
    trigrafos['a'-'a']['i'-'a']['s'-'a'] = 2.337;
}

#endif
