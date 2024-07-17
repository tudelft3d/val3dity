


Vue.component('feature-item', {
    props: ['feature'],
    template: `
    <li class="m-2">
        <i class="fas" :class="[ isOpen ? 'fa-minus' : 'fa-plus' ]" @click="toggle()"></i> 
        <span class="badge badge-primary">{{ feature.type }}</span>
        <span class="badge" :class="[ feature.validity ? 'badge-success' : 'badge-danger' ]">{{ feature.validity ? 'valid' : 'invalid' }}</span>
        {{ feature.id }}
        <ul class="list-unstyled ml-5" v-show="isOpen">
            <li :error="e" v-for="e in feature.errors"><span class="badge badge-warning">Error {{ e.code }}</span> <span class="badge badge-light">{{ e.description }}</span> {{ e.id }} | info={{ e.info }}</li>
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
        console.log("fetching the report from a URL");
        var theurl = fre;
        var self = this;
        $.getJSON(theurl, 
          function(data) {
            // console.log(data);
            self.set_report_data(data);
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
            this.set_report_data(jre);
          }
          else {
            console.log("This is not a val3dity report JSON file. Abort.");
            alert("This is not a val3dity report file (must be JSON & v2.2+).");
            return;
          }
        }
      },
      set_report_data(data) {
        this.report = data;
        this.file_loaded = true;
        this.error_filters = this.report.all_errors;
      }
    },
    computed: {
        filteredFeatures: function () {
            if (this.feature_filter == "valid") {
              var new_features = $.extend(true, [], this.report.features);

              return new_features.filter(function f(p) {
                if (p.validity == true) {
                  return true;
                }
              });
            }
            else if (this.feature_filter == "invalid") {
              var new_features = $.extend(true, [], this.report.features);

              let error_filters = this.error_filters;

              return new_features.filter(function f(p) {
                var show = false;

                if (p.errors && p.errors.some(e => error_filters.includes(e.code))) {
                  show = true;
                }

                return show;
              });
            }
            else if (this.feature_filter == "all") {
              return this.report.features;
            }
        }
    }
})

Vue.config.devtools = true


