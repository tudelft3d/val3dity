Vue.component('primitive-item', {
    props: ['primitive'],
    template: `
    <li>
        <i class="fas" :class="[ isOpen ? 'fa-minus' : 'fa-plus' ]" @click="toggle()"></i> <span class="badge badge-success">{{ primitive.type }}</span> {{ primitive.id }}
        <ul v-show="isOpen">
            <li :primitive="e" v-for="e in primitive.errors">{{ e.description }}</li>
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
        <i class="fas" :class="[ isOpen ? 'fa-minus' : 'fa-plus' ]" @click="toggle()"></i> <span class="badge badge-primary">{{ feature.type }}</span> {{ feature.id }}
        <ul class="list-unstyled ml-5" v-show="isOpen">
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
        }
    },
    methods: {
      reset() {
        this.report = {};
        this.file_loaded = false;
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