

Vue.component('primitive-item', {
    props: ['primitive'],
    template: `
    <li>
        <i class="fas" :class="[ isOpen ? 'fa-minus' : 'fa-plus', primitive.validity ? 'text-white' : '' ]" @click="toggle()"></i> 
        <span class="badge badge-secondary">{{ primitive.type }}</span>
        <span class="badge" :class="[ primitive.validity ? 'badge-success' : 'badge-danger' ]">{{ primitive.validity ? 'valid' : 'invalid' }}</span>
        {{ primitive.id }}
        <ul v-show="isOpen">
            <li :primitive="e" v-for="e in primitive.errors"><span class="badge badge-warning">Error {{ e.code }}</span> {{ e.description }} | id={{ e.id }} | info={{ e.info }}</li>
        </ul>
    </li>
    `,
    data: function() {
        return {
            isOpen: false
        }
    },
    methods: {
        toggle() {
            this.isOpen = !this.isOpen;
        }
    }
})

Vue.component('feature-item', {
    props: ['feature'],
    template: `
    <li class="m-2">
        <i class="fas" :class="[ isOpen ? 'fa-minus' : 'fa-plus' ]" @click="toggle()"></i> 
        <span class="badge badge-primary">{{ feature.type }}</span>
        <span class="badge" :class="[ feature.validity ? 'badge-success' : 'badge-danger' ]">{{ feature.validity ? 'valid' : 'invalid' }}</span>
        {{ feature.id }}
        <ul class="list-unstyled ml-5" v-show="isOpen">
            <li :error="e" v-for="e in feature.errors"><span class="badge badge-warning">Error {{ e.code }}</span> {{ e.description }} | id={{ e.id }} | info={{ e.info }}</li>
            <primitive-item :primitive="p" v-for="p in feature.primitives"></primitive-item>
        </ul>
    </li>
    `,
    data: function() {
        return {
            isOpen: false
        }
    },
    methods: {
        toggle() {
            this.isOpen = !this.isOpen;
        }
    }
})

var app = new Vue({
    el: '#app',
    data: function() {
        var fre = this.getUrlVars()["f"];
        if (fre != null) {
          console.log("URL params for the report to load.");
          this.load_report_from_url(fre);
        }
        return {
          file_loaded: false,
          report: {},
          search_term: null,
          feature_filter: "all",
          error_filters: [],
        }
    },
    methods: {
      getUrlVars() {
        var vars = {};
        var parts = window.location.href.replace(/[?&]+([^=&]+)=([^&]*)/gi, function(m,key,value) {
            vars[key] = value;
        });
        return vars;
      },
      load_report_from_url(fre) {
        // var dataURL = 'http://homepage.tudelft.nl/23t4p/temp/r2.json';
        console.log("fetching the report from a URL");
        var hackcors = 'https://cors-anywhere.herokuapp.com/';
        var theurl = hackcors + fre;
        var self = this;
        $.getJSON(theurl, 
          function(data) {
            // console.log(data);
            self.report = data;
            self.file_loaded = true;
        });
        console.log("fetched.");
      },
      reset() {
        this.report = {};
        this.filter_value = false;
        this.file_loaded = false;
        this.error_filters = [];
      },
      getAlertClass(percentage) {
        if( percentage > 80) {
            return ['alert-success'];
        }
        else if (percentage > 50) {
            return ['alert-warning'];
        }
        else {
            return ['alert-danger'];
        }
      },
      getOverviewPercentage(report_list) {
        var total = report_list.reduce((acc, item) => acc + item.total, 0);
        var valid = report_list.reduce((acc, item) => acc + item.valid, 0);
        if (total == 0){
            return 0;
        }
        return Math.floor((valid / total) * 100);;
      },  
      selectedFile() {
        console.log("Selected a val3dity report JSON file...");
        console.log(this.$refs.reportFile.files[0]);

        let file = this.$refs.reportFile.files[0];
        if (!file || file.type != "application/json")
        {
          console.log("This is not a val3dity report JSON file. Abort.");
          alert("This is not a val3dity report file (must be JSON & v2.2+).");
          return;
        }

        let reader = new FileReader();
        reader.readAsText(file, "UTF-8");
        reader.onload = evt => {
          jre = JSON.parse(evt.target.result);
          if (jre.type == "val3dity_report") {
            this.report = jre;
            this.file_loaded = true;
            this.error_filters = this.report.all_errors;
          }
          else {
            console.log("This is not a val3dity report JSON file. Abort.");
            alert("This is not a val3dity report file (must be JSON & v2.2+).");
            return;
          }
        }
      }
    },
    computed: {
        filteredFeatures: function () {
            if (this.feature_filter == "valid") {
                filter = f => { return f.validity; }
            }
            else if (this.feature_filter == "invalid") {
                // filter = f => { return !f.validity; }
                let error_code = this.feature_filter;
                filter = f => {
                  if (f.errors.some(e => this.error_filters.includes(e.code))) {
                    return true;
                  }

                  return f.primitives.some(p => {
                    return 'errors' in p && p.errors.some(e => this.error_filters.includes(e.code));
                  });
                }
            }
            else if (this.feature_filter == "all") {
                filter = f => {return true; }
            }
            return this.report.features.filter(filter);
        }
    }
})

Vue.config.devtools = true


