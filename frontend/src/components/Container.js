import React, {Component} from 'react';
import axios from 'axios';
import InputContainer from './InputContainer';
import OutputContainer from './OutputContainer';

const morf_result=[
    [{"form":"Время","selectedAnalysis":"время","selectedTag":"NCNSAI0000",
      "analysis":[{"lemma":"время","tag":"NCFSAI0000","prob":"0.872347"},   {"lemma":"время","tag":"NCNSAI0000","prob":"0.127644"},{"lemma":"время","tag":"NP","prob":"0.000009"}]},

     {"form":"приближалось","selectedAnalysis":"приближалось","selectedTag":"VDSAS0NAA00","analysis":[{"lemma":"приближалось","tag":"VDSAS0NAA00","prob":"1.000000"}]},

     {"form":"к","selectedAnalysis":"к","selectedTag":"B0","analysis":[{"lemma":"к","tag":"B0","prob":"1.000000"}]},

     {"form":"одиннадцати-ноль-ноль","selectedAnalysis":"одиннадцати-ноль-ноль","selectedTag":"NCFSMI0000",
      "analysis":[{"lemma":"одиннадцати-ноль-ноль","tag":"NCNSMI0000","prob":"0.606741"},{"lemma":"одиннадцати-ноль-ноль","tag":"NCFSMI0000","prob":"0.314607"},{"lemma":"одиннадцати-ноль-ноль","tag":"NCNSMAF000","prob":"0.078652"}]},

     {"form":",","selectedAnalysis":",","selectedTag":"Fc","analysis":[{"lemma":",","tag":"Fc","prob":"1.000000"}]},{"form":"и","selectedAnalysis":"и","selectedTag":"C0","analysis":[{"lemma":"и","tag":"C0","prob":"1.000000"}]},{"form":"в","selectedAnalysis":"в","selectedTag":"B0","analysis":[{"lemma":"в","tag":"B0","prob":"1.000000"}]},

     {"form":"отделе","selectedAnalysis":"отдел","selectedTag":"NCOSMI0000",
      "analysis":[{"lemma":"отдел","tag":"NCOSMI0000","prob":"1.000000"}]},

     {"form":"документации","selectedAnalysis":"документации","selectedTag":"NCGSFI0000",
      "analysis":[{"lemma":"документации","tag":"NCGSFI0000","prob":"0.583334"},{"lemma":"документации","tag":"NCDSFI0000","prob":"0.250000"},{"lemma":"документации","tag":"NCOSFI0000","prob":"0.083334"},{"lemma":"документации","tag":"NCFPFI0000","prob":"0.083333"}]},

     {"form":",","selectedAnalysis":",","selectedTag":"Fc","analysis":[{"lemma":",","tag":"Fc","prob":"1.000000"}]},

     {"form":"где","selectedAnalysis":"где","selectedTag":"P0",
      "analysis":[{"lemma":"где","tag":"P0","prob":"0.999721"},{"lemma":"где","tag":"D000","prob":"0.000279"}]},

     {"form":"работал","selectedAnalysis":"работать","selectedTag":"VDSMS0N0A00",
      "analysis":[{"lemma":"работать","tag":"VDSMS0N0A00","prob":"1.000000"}]},

     {"form":"Уинстон","selectedAnalysis":"уинстон","selectedTag":"NP","analysis":[{"lemma":"уинстон","tag":"NP","prob":"1.000000"}]},

     {"form":",","selectedAnalysis":",","selectedTag":"Fc","analysis":[{"lemma":",","tag":"Fc","prob":"1.000000"}]},

     {"form":"сотрудники","selectedAnalysis":"сотрудник","selectedTag":"NCNPMA0000",
      "analysis":[{"lemma":"сотрудник","tag":"NCNPMA0000","prob":"1.000000"}]},

     {"form":"выносили","selectedAnalysis":"выносить","selectedTag":"VDP0S0N0M00",
      "analysis":[{"lemma":"выносить","tag":"VDP0S0N0M00","prob":"0.533333"},{"lemma":"выносить","tag":"VDP0S0F0M00","prob":"0.233333"},{"lemma":"вынашивать","tag":"VDP0S0F0000","prob":"0.233333"}]},

     {"form":"стулья","selectedAnalysis":"стул","selectedTag":"NCFPMI0000","analysis":[{"lemma":"стул","tag":"NCFPMI0000","prob":"0.525940"},{"lemma":"стул","tag":"NCNPMI0000","prob":"0.474060"}]},

     {"form":"из","selectedAnalysis":"из","selectedTag":"B0","analysis":[{"lemma":"из","tag":"B0","prob":"1.000000"}]},

     {"form":"кабин","selectedAnalysis":"кабина","selectedTag":"NCGPFI0000",
      "analysis":[{"lemma":"кабина","tag":"NCGPFI0000","prob":"1.000000"}]},

     {"form":"и","selectedAnalysis":"и","selectedTag":"C0","analysis":[{"lemma":"и","tag":"C0","prob":"1.000000"}]},

     {"form":"расставляли","selectedAnalysis":"расставлять","selectedTag":"VDP0S0N0M00",
      "analysis":[{"lemma":"расставлять","tag":"VDP0S0N0M00","prob":"1.000000"}]},

     {"form":"в","selectedAnalysis":"в","selectedTag":"B0",
      "analysis":[{"lemma":"в","tag":"B0","prob":"1.000000"}]},

     {"form":"середине","selectedAnalysis":"середина","selectedTag":"NCOSFI0000",
      "analysis":[{"lemma":"середина","tag":"NCOSFI0000","prob":"0.850857"},{"lemma":"середина","tag":"NCDSFI0000","prob":"0.149143"}]},

     {"form":"холла","selectedAnalysis":"холла","selectedTag":"NCGSMI0000",
      "analysis":[{"lemma":"холла","tag":"NCGSMI0000","prob":"0.600001"},{"lemma":"холла","tag":"NCGSMAF000","prob":"0.399999"}]},

     {"form":"перед","selectedAnalysis":"перед","selectedTag":"NCNSMI0000",
      "analysis":[{"lemma":"перед","tag":"NCNSMI0000","prob":"0.999321"},{"lemma":"перед","tag":"NCFSMI0000","prob":"0.000679"}]},

     {"form":"большим","selectedAnalysis":"больший","selectedTag":"ACSA0F000",
      "analysis":[{"lemma":"больший","tag":"ACSA0F000","prob":"0.243783"},{"lemma":"больший","tag":"ACSM0F000","prob":"0.243783"},{"lemma":"большой","tag":"ACSA0F000","prob":"0.243783"},{"lemma":"большой","tag":"ACSM0F000","prob":"0.243783"},{"lemma":"больший","tag":"ADP00F000","prob":"0.012417"},{"lemma":"большой","tag":"ADP00F000","prob":"0.012417"},{"lemma":"большее","tag":"NCCSAI0000","prob":"0.000035"}]},

     {"form":"телекраном","selectedAnalysis":"телекраном","selectedTag":"NCCSMI0000","analysis":[{"lemma":"телекраном","tag":"NCCSMI0000","prob":"1.000000"}]},

     {"form":"—","selectedAnalysis":"—","selectedTag":"Fz","analysis":[{"lemma":"—","tag":"Fz","prob":"1.000000"}]},

     {"form":"собирались","selectedAnalysis":"собирались","selectedTag":"VDP0S0NAA00",
      "analysis":[{"lemma":"собирались","tag":"VDP0S0NAA00","prob":"0.985294"},{"lemma":"собирались","tag":"VDP0S0N0A00","prob":"0.009804"},{"lemma":"собирались","tag":"VDP0S0FAA00","prob":"0.004902"}]},

     {"form":"на","selectedAnalysis":"на","selectedTag":"B0","analysis":[{"lemma":"на","tag":"B0","prob":"0.999321"},{"lemma":"на","tag":"T0","prob":"0.000679"}]},

     {"form":"двухминутку","selectedAnalysis":"двухминутку","selectedTag":"NCFSFI0000",
      "analysis":[{"lemma":"двухминутку","tag":"NCFSFI0000","prob":"1.000000"}]},

     {"form":"ненависти","selectedAnalysis":"ненависти","selectedTag":"NCGSFI0000",
      "analysis":[{"lemma":"ненависти","tag":"NCGSFI0000","prob":"0.753165"},{"lemma":"ненависти","tag":"NCOSFI0000","prob":"0.189873"},{"lemma":"ненависти","tag":"NCDSFI0000","prob":"0.056962"}]},

     {"form":".","selectedAnalysis":".","selectedTag":"Fp",
      "analysis":[{"lemma":".","tag":"Fp","prob":"1.000000"}]}
    ],

    [{"form":"Уинстон","selectedAnalysis":"уинстон","selectedTag":"NCNSMAN000",
      "analysis":[{"lemma":"уинстон","tag":"NCNSMAN000","prob":"0.661396"},{"lemma":"уинстон","tag":"NP","prob":"0.338604"}]},

    {"form":"приготовился","selectedAnalysis":"приготавливаться","selectedTag":"VDSMS0F0A00",
     "analysis":[{"lemma":"приготавливаться","tag":"VDSMS0F0A00","prob":"0.500000"},{"lemma":"приготовляться","tag":"VDSMS0F0A00","prob":"0.500000"}]},

     {"form":"занять","selectedAnalysis":"занимать","selectedTag":"VI0000F0000",
      "analysis":[{"lemma":"занимать","tag":"VI0000F0000","prob":"1.000000"}]},

     {"form":"свое","selectedAnalysis":"свой","selectedTag":"RFSA00","analysis":[{"lemma":"свой","tag":"RFSA00","prob":"0.884385"},{"lemma":"свое","tag":"EFSAI00","prob":"0.082092"},{"lemma":"свой","tag":"RNSA00","prob":"0.026510"},{"lemma":"свое","tag":"ENSAI00","prob":"0.007013"}]},

     {"form":"место","selectedAnalysis":"место","selectedTag":"NCFSAI0000","analysis":[{"lemma":"место","tag":"NCFSAI0000","prob":"0.727983"},{"lemma":"место","tag":"NCNSAI0000","prob":"0.272017"}]},

     {"form":"в","selectedAnalysis":"в","selectedTag":"B0","analysis":[{"lemma":"в","tag":"B0","prob":"1.000000"}]},

     {"form":"средних","selectedAnalysis":"средний","selectedTag":"AOP00F000",
      "analysis":[{"lemma":"средний","tag":"AGP00F000","prob":"0.821017"},{"lemma":"средний","tag":"AOP00F000","prob":"0.176949"},{"lemma":"среднее","tag":"NCGPAI0000","prob":"0.000678"},{"lemma":"среднее","tag":"NCOPAI0000","prob":"0.000678"},{"lemma":"средний","tag":"AFP0AF000","prob":"0.000678"}]},

     {"form":"рядах","selectedAnalysis":"ряд","selectedTag":"NCOPMI0000",
      "analysis":[{"lemma":"ряд","tag":"NCOPMI0000","prob":"1.000000"}]},

     {"form":",","selectedAnalysis":",","selectedTag":"Fc","analysis":[{"lemma":",","tag":"Fc","prob":"1.000000"}]},

     {"form":"и","selectedAnalysis":"и","selectedTag":"C0","analysis":[{"lemma":"и","tag":"C0","prob":"1.000000"}]},

     {"form":"тут","selectedAnalysis":"тут","selectedTag":"P0",
      "analysis":[{"lemma":"тут","tag":"P0","prob":"0.998291"},{"lemma":"тута","tag":"NCGPFI0000","prob":"0.001240"},{"lemma":"тут","tag":"NCNSMI0000","prob":"0.000458"},{"lemma":"тут","tag":"NCFSMI0000","prob":"0.000011"}]},

     {"form":"неожиданно","selectedAnalysis":"неожиданно","selectedTag":"D000",
      "analysis":[{"lemma":"неожиданно","tag":"D000","prob":"0.973786"},{"lemma":"неожиданно","tag":"A0SA0S000","prob":"0.026214"}]},

     {"form":"появились","selectedAnalysis":"появляться","selectedTag":"VDP0S0F0A00","analysis":[{"lemma":"появляться","tag":"VDP0S0F0A00","prob":"1.000000"}]},

     {"form":"еще","selectedAnalysis":"еще","selectedTag":"D000","analysis":[{"lemma":"еще","tag":"D000","prob":"0.940663"},{"lemma":"еще","tag":"T0","prob":"0.059337"}]},

     {"form":"двое","selectedAnalysis":"двое","selectedTag":"ZN0000","analysis":[{"lemma":"двое","tag":"ZN0000","prob":"0.857230"},{"lemma":"двое","tag":"ZF00I0","prob":"0.142770"}]},

     {"form":":","selectedAnalysis":":","selectedTag":"Fd","analysis":[{"lemma":":","tag":"Fd","prob":"1.000000"}]},

     {"form":"лица","selectedAnalysis":"лицо","selectedTag":"NCNPAA0000","analysis":[{"lemma":"лицо","tag":"NCGSAA0000","prob":"0.309607"},{"lemma":"лицо","tag":"NCGSAI0000","prob":"0.309607"},{"lemma":"лицо","tag":"NCNPAA0000","prob":"0.154221"},{"lemma":"лицо","tag":"NCNPAI0000","prob":"0.154221"},{"lemma":"лицо","tag":"NCFPAI0000","prob":"0.072344"}]},

     {"form":"знакомые","selectedAnalysis":"знакомая","selectedTag":"NCNPFA0000","analysis":[{"lemma":"знакомый","tag":"ANP00F000","prob":"0.412818"},{"lemma":"знакомая","tag":"NCNPFA0000","prob":"0.293461"},{"lemma":"знакомый","tag":"NCNPMA0000","prob":"0.293461"},{"lemma":"знакомый","tag":"AFP0IF000","prob":"0.000259"}]},

     {"form":",","selectedAnalysis":",","selectedTag":"Fc","analysis":[{"lemma":",","tag":"Fc","prob":"1.000000"}]},

     {"form":"но","selectedAnalysis":"но","selectedTag":"C0","analysis":[{"lemma":"но","tag":"C0","prob":"0.999735"},{"lemma":"но","tag":"J00","prob":"0.000265"}]},

     {"form":"разговаривать","selectedAnalysis":"разговаривать","selectedTag":"VI0000N0A00","analysis":[{"lemma":"разговаривать","tag":"VI0000N0A00","prob":"1.000000"}]},

     {"form":"с","selectedAnalysis":"с","selectedTag":"B0","analysis":[{"lemma":"с","tag":"B0","prob":"1.000000"}]},

     {"form":"ними","selectedAnalysis":"они","selectedTag":"ECP0000","analysis":[{"lemma":"они","tag":"ECP0000","prob":"1.000000"}]},

     {"form":"ему","selectedAnalysis":"он","selectedTag":"E0S0000","analysis":[{"lemma":"он","tag":"E0S0000","prob":"0.500000"},{"lemma":"оно","tag":"E0S0000","prob":"0.500000"}]},

     {"form":"не","selectedAnalysis":"не","selectedTag":"T0","analysis":[{"lemma":"не","tag":"T0","prob":"1.000000"}]},

     {"form":"приходилось","selectedAnalysis":"приходилось","selectedTag":"VDSAS0NAA00","analysis":[{"lemma":"приходилось","tag":"VDSAS0NAA00","prob":"0.759956"},{"lemma":"приходилось","tag":"VDSAS0N0A00","prob":"0.238967"},{"lemma":"приходилось","tag":"VDSAS0F0A00","prob":"0.001077"}]},

     {"form":".","selectedAnalysis":".","selectedTag":"Fp","analysis":[{"lemma":".","tag":"Fp","prob":"1.000000"}]}]
];
const ServerURL = "http://localhost:3001/";

class Container extends Component {
    constructor() {
        super();
        this.state= {
            selectedOption: "morf",
            analysisOpts: [],
            inputText: ""
        };

        this.handleFormSubmit = this.handleFormSubmit.bind(this);
    }

    handleFormSubmit(inputData) {
      this.setState({
        selectedOption: inputData.selectedOption,
        analysisOpts: inputData.analysisOpts,
        inputText: inputData.inputText
      }, () => {
        let url = ServerURL;
        if (inputData.selectedOption === "pos-tag") {
          url += "pos-tagger";
        } else if (inputData.selectedOption === "morf") {
          url += "morf";
        }
        axios.post(url, {
          selectedOption: inputData.selectedOption,
          analysisOpts: inputData.analysisOpts,
          inputText: inputData.inputText
        })
          .then((response) => {
            console.log(response);
          })
          .catch((error) => {
            console.log(error);
          })
      });
    }

    render() {
        return (
        <div className="container">
            <section className="input-section">
                <InputContainer onSubmitForm={ this.handleFormSubmit }/>
            </section>
            <section className="output-section">
                <OutputContainer result={ morf_result } option={this.state.selectedOption}/>
            </section>
        </div>
    );
  }
};

export default Container;
