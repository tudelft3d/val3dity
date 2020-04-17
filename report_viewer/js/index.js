Vue.component('primitive-item', {
    props: ['primitive'],
    template: `
    <li>
        <i class="fas" :class="[ isOpen ? 'fa-minus' : 'fa-plus' ]" @click="toggle()"></i> 
        <span v-if="primitive.validity == true" class="badge badge-success">{{ primitive.type }}</span> 
        <span v-else class="badge badge-danger">{{ primitive.type }}</span> 
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
        <span v-if="feature.validity == true" class="badge badge-success">{{ feature.type }}</span> 
        <span v-else class="badge badge-danger">{{ feature.type }}</span> 
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
        return {
            file_loaded: false,
            report: {},
            search_term: null
        }
    },
    methods: {
      reset() {
        this.report = {};
        this.file_loaded = false;
      },
      get_percent_primitives() {
        if (this.report.primitives_overview == null) {
            return 0;
        }
        var total = this.report.primitives_overview.reduce((acc, item) => acc + item.total, 0);
        var valid = this.report.primitives_overview.reduce((acc, item) => acc + item.valid, 0);
        if (total == 0){
            return 0;
        }
        return Math.floor((valid / total) * 100);;
      },
      get_percent_features() {
        if (this.report.features_overview == null) {
            return 0;
        }
        var total = this.report.features_overview.reduce((acc, item) => acc + item.total, 0);
        var valid = this.report.features_overview.reduce((acc, item) => acc + item.valid, 0);
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
          return;
        }

        let reader = new FileReader();
        reader.readAsText(file, "UTF-8");
        reader.onload = evt => {
          jre = JSON.parse(evt.target.result);
          this.report = jre;
          this.file_loaded = true;
        }
      }
    }
})

Vue.config.devtools = true